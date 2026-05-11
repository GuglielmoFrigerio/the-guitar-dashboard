# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this project is

A JUCE-based C++20 desktop application — a "guitar dashboard" that plays synchronized backing tracks while sending MIDI program changes / scene changes to a Fractal Audio AxeFx II/III amp modeler. A live-performance tool: songs are described in XML config files (`Configuration/Focused.xml`, `Configuration/Complete.xml`) listing the audio track, markers, and the ordered list of patches the guitarist will step through during the song.

## Build

Source of truth is `the-guitar-dashboard.jucer` (Projucer project). Open it in Projucer to regenerate `JuceLibraryCode/` and the platform projects under `Builds/` — these are partially gitignored and re-saving the .jucer is the canonical way to update them.

- **Windows**: Open `Builds/VisualStudio2022/the-guitar-dashboard.sln` in VS2022. JUCE modules are expected at `C:\JUCE\modules` (configured in the .jucer for the VS2022 export). After editing `the-guitar-dashboard.jucer` (e.g., to add a new source file), re-save it in Projucer before building.
- **macOS / iOS**: separate exports under `Builds/MacOSX/` and `Builds/iOS/` with their own JUCE module paths (`../../juce` and `~/Projects/Guglielmo/JUCE/modules` respectively).

There is no test suite, no linter, and no CI in this repo.

## Architecture

### Two engines coexist

The codebase is mid-migration. `MainComponent.cpp` has a `bool newUi` flag that picks between them:

- **Existing engine** (default): `VirtualBandPage` → `VirtualBand` → `Song` (abstract) / `TheLambsSong` (concrete) → `Track`s of `EventList`s of `Event`s. Timing driven by `PlaybackEngine` (a `juce::HighResolutionTimer`) using musical *clicks* (`DefaultClicksPerBeat = 480` per beat, BPM-derived). All "playable" objects implement `IPlaybackTarget::{play, seek, onTick}` keyed off `(currentClick, previousClick)`.
- **NewEngine** (`Source/NewEngine/`, namespace `ne`, branch `playback-engine`): sample-accurate replacement. `MusicSequencer` owns a `TempoMap` (PPQ=960, ticks↔samples), a `MediaBay` (sample buffer cache), a `VoiceEngine` (32-voice pool with a 128-entry trigger FIFO), and a vector of `TrackBase`s (`AudioTrack`, `SampleTrack`, `NewMetronomeTrack`). UI commands cross the thread boundary via `CommandQueue` (lock-free `juce::AbstractFifo` of `Command{Play|Stop|SetBpm|SeekSamples}`). Per-block rendering is driven by a `RenderContext` carrying `(startSample, endSample, startTick, samplesPerBeat, TempoMap*)`.

When extending playback features, decide which engine you're touching and stay in its idiom — don't translate clicks/BPM patterns into the sample-accurate code or vice versa.

### Existing-engine call graph (the parts that aren't obvious from a single file)

- `VirtualBand` is the central hub. It implements `IDeviceHost` (hands out `MidiDevice*` per `FractalDeviceType`), owns the `juce::AudioTransportSource`, the `SongCollection`, the `FractalDevice`s discovered at startup, the `SampleEngine`, and the `AudioRecorder`. It loads the active library from one of the `Configuration/*.xml` files (selected via the libraries combo box). The XML defines `Library → Song → Track + ordered Patch list`, where each Patch is a program-change number with an AxeFx scene and optional `MidiModifier` (CC ramp).
- `Song::activate()` is called when the user picks a song. `TheLambsSong` is currently the only concrete `Song`; it loads the audio file via `AudioFormatReaderSource`, parses patches into `SongPatch`s, sets up MIDI tracks/recorder/TriplePlay input, and constructs its own `PlaybackEngine`.
- The chain UI → audio is: keyboard / `PlayerComponent` button → `VirtualBand::toggleStartStop` → `m_transportSource.start()` (for backing-track mode) **and** `m_pActiveSong->onPlayerStateUpdated()` which drives the song's `PlaybackEngine` for MIDI/automation events.
- `IMidiInputTarget` (e.g., `TheLambsSong::onNoteOn`) lets a song react to TriplePlay input — used for trigger-based patch advancement on certain songs.

### Conventions used throughout

- Member fields prefixed `m_`. Raw pointers additionally prefixed `p` (`m_pPlayerComponent`). `unique_ptr` fields suffixed `Ptr` (`m_songCollectionPtr`).
- `#pragma once` everywhere. `JUCE_STRICT_REFCOUNTEDPOINTER=1` is on.
- Most "Created: …, Author: gugli" header comments are Projucer boilerplate — don't treat them as meaningful documentation.
- User-facing app properties (last library, etc.) are persisted via `juce::PropertiesFile` under the OS user application data directory; see `MainComponent::propInit`.

## Resources & gitignored content

`Resources/Tracks/`, `Resources/Samples/`, and `Resources/recordings/` are gitignored — they hold real audio/MIDI files referenced by the XML libraries, but each developer brings their own. Do not assume any specific track file exists when reading code that loads from these paths; the filenames in `Configuration/*.xml` are the contract.

## Session notes

- Current working branch is `playback-engine` — active work is the NewEngine port. The existing engine still compiles and runs.
- `documentation/readme.md` is a stub pointing to an Excalidraw diagram link.

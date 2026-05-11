/*
  ==============================================================================

    MusicSequencerComponent.h
    Created: 2 Feb 2026 1:55:35pm
    Author:  frigeriog-adm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MusicSequencer.h"
#include "NeSongCollection.h"
#include "NeSongListComponent.h"
#include "../PlayerComponent.h"

//==============================================================================
class MusicSequencerComponent  :    public juce::AudioAppComponent,
                                    public juce::Slider::Listener
{
private:
    ne::MusicSequencer m_musicSequencer;
    juce::Slider m_bpmSlider;
    juce::Label  m_bpmLabel;
    juce::ComboBox m_librariesComboBox;
    juce::Label m_librariesLabel;
    ne::SongListComponent m_songListComponent;
    PlayerComponent m_playerComponent;

    std::unique_ptr<juce::XmlElement> m_configElementPtr;
    std::unique_ptr<ne::SongCollection> m_songCollectionPtr;

public:
    MusicSequencerComponent();
    ~MusicSequencerComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

private:
    void releaseResources() override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

    void loadConfig();
    void populateLibraries();
    void loadLibrary(const juce::String& libraryName);
    void onSongSelected(int songIndex);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicSequencerComponent)
};

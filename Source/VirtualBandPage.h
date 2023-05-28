/*
  ==============================================================================

    VirtualBandPage.h
    Created: 14 Aug 2021 10:48:50am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <memory>
#include <JuceHeader.h>
#include "VirtualBand.h"
#include "SongListComponent.h"
#include "ProgramChangesComponent.h"
#include "PlayerComponent.h"
#include "KeyManager.h"
#include "NotificationComponent.h"

class VirtualBandPage : 
    public juce::AudioAppComponent, 
    public juce::KeyListener,
    public juce::ChangeListener,
    private juce::Timer
{
private:    // fields
    std::unique_ptr<VirtualBand> m_virtualBandPtr;
    juce::TextButton m_loadSongLibraryButton;
    std::unique_ptr<juce::FileChooser> m_chooserPtr;
    juce::ComboBox m_librariesComboBox;
    SongListComponent m_songListComponent;
    ProgramChangesComponent m_programChangesComponent;
    juce::ApplicationProperties& m_properties;
    bool m_firstResize = true;
    PlayerComponent m_playerComponent;
    KeyManager m_trackPlayerKeyManager;
    NotificationComponent m_notificationComponent;
    std::unordered_map<int, std::function<void(const juce::KeyPress& key, Component* originatingComponent)>> m_keyHandlerMap;

private:    // implementation
    void chooseSongLibrary();
    void loadSongLibrary(juce::File& file);
    void onFirstResized();
    void releaseResources() override;
    void timerCallback() override;
    void setupKeyHandlers();

private:    // keyboard
    void nextProgramChange();
    void previousProgramChange();
    void nextMarker();
    void previousMarker();

private:    // KeyListener
    bool keyPressed(const juce::KeyPress& key, Component* originatingComponent) override;
    bool keyStateChanged(bool isKeyDown, Component* originatingComponent) override;


public:     // interface
    VirtualBandPage(juce::ApplicationProperties& properties);
    ~VirtualBandPage() override;

    void resized() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void changeListenerCallback(juce::ChangeBroadcaster*) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VirtualBandPage)

};

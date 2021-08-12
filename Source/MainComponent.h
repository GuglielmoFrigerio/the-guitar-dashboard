#pragma once

#include <JuceHeader.h>
#include "LimitFollower.h"
#include "Oscillator.h"
#include "Lfo.h"
#include "PitchDetector.h"
#include "SetupPage.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : 
    public juce::AudioAppComponent,
    public juce::ChangeListener,
    public juce::Button::Listener,
    private juce::Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:    // implementation
    void timerCallback() override;
    void changeListenerCallback(juce::ChangeBroadcaster*) override;
    void buttonClicked(juce::Button* button) override;
    void chooseInputChannelIndex();

private:
    LimitFollower m_limitFollower;
    std::unique_ptr<Oscillator> m_osc1Ptr;
    std::unique_ptr<Oscillator> m_osc2Ptr;
    std::unique_ptr<Lfo> m_lfo;
    std::unique_ptr<PitchDetector> m_pitchDetector;
    juce::TextButton m_openSettings;
    juce::TextButton m_closeSettings;
    std::unique_ptr<SetupPage> m_setupPagePtr;

    float m_sum = 0.;
    int m_inputChannelIndex = -1;
    int m_preferredInputChannelIndex = 4;
    int m_midiNote;
    float m_volume = 0.f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

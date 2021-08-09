#pragma once

#include <JuceHeader.h>
#include "LimitFollower.h"
#include "Oscillator.h"
#include "Lfo.h"
#include "PitchDetector.h"

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
    void logMessage(const juce::String& m);
    void dumpDeviceInfo();
    static juce::String getListOfActiveBits(const juce::BigInteger& b);
    void timerCallback() override;
    void changeListenerCallback(juce::ChangeBroadcaster*) override;
    void buttonClicked(juce::Button* button) override;

private:
    //==============================================================================
    juce::AudioDeviceSelectorComponent audioSetupComp;
    juce::Label cpuUsageLabel;
    juce::Label cpuUsageText;
    juce::TextEditor diagnosticsBox;

    LimitFollower m_limitFollower;
    std::unique_ptr<Oscillator> m_osc1Ptr;
    std::unique_ptr<Oscillator> m_osc2Ptr;
    std::unique_ptr<Lfo> m_lfo;
    std::unique_ptr<PitchDetector> m_pitchDetector;
    juce::TextButton m_saveCorrelationButton;

    float m_sum;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

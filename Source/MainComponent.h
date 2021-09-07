#pragma once

#include <JuceHeader.h>
#include "LimitFollower.h"
#include "Oscillator.h"
#include "Lfo.h"
#include "PitchDetector.h"
#include "SetupPage.h"

class VirtualBandPage;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : 
    public juce::Component,
    public juce::Button::Listener,
    private juce::Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:    // implementation
    void timerCallback() override;
    void buttonClicked(juce::Button* button) override;
    void propInit();

private:
    std::unique_ptr<VirtualBandPage> m_virtualBandPagePtr;
    juce::TextButton m_setupButton;
    juce::TextButton m_virtualBandButton;
    std::unique_ptr<juce::Component> m_activePage;
    juce::ApplicationProperties m_properties;

    float m_sum = 0.;
    int m_inputChannelIndex = -1;
    int m_preferredInputChannelIndex = 4;
    int m_midiNote;
    float m_volume = 0.f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

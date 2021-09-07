/*
  ==============================================================================

    SetupPage.h
    Created: 12 Aug 2021 12:15:06pm
    Author:  gugli

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SetupPage  : public juce::Component
{
private:    // fields
    //==============================================================================
    juce::AudioDeviceSelectorComponent audioSetupComp;
    juce::Label cpuUsageLabel;
    juce::Label cpuUsageText;
    juce::TextEditor diagnosticsBox;
    juce::AudioDeviceManager& deviceManager;

private:    // implementation
    void dumpDeviceInfo();
    void logMessage(const juce::String& m);
    juce::String getListOfActiveBits(const juce::BigInteger& b);

public:
    SetupPage(juce::AudioDeviceManager& deviceManager);
    ~SetupPage() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SetupPage)
};

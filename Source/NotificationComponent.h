/*
  ==============================================================================

    NotificationComponent.h
    Created: 8 Apr 2022 9:58:15pm
    Author:  gugli

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class NotificationComponent  : public juce::Component
{
public:
    NotificationComponent();
    ~NotificationComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NotificationComponent)
};

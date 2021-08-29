/*
  ==============================================================================

    ProgramChangesComponent.h
    Created: 27 Aug 2021 4:08:02pm
    Author:  gugli

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Track;

//==============================================================================
/*
*/
class ProgramChangesComponent  : public juce::Component, public juce::Button::Listener
{
private:    // fields
    juce::OwnedArray<juce::TextButton> m_programChanceTiles;

private:    // implementation
    virtual void buttonClicked(juce::Button* pButton) override;

public:
    ProgramChangesComponent();
    ~ProgramChangesComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void update(const Track* pTrack);

    std::function<void(int)> onProgramChangeSelected;

    void selectProgramChange(int programChangeIndex);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProgramChangesComponent)
};

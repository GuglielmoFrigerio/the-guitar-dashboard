/*
  ==============================================================================

    ProgramChangesComponent.h
    Created: 27 Aug 2021 4:08:02pm
    Author:  gugli

  ==============================================================================
*/

#pragma once

#include <memory>
#include <JuceHeader.h>
#include "TilesLookAndFeel.h"
#include "ValueAnimator.h"

class Track;

//==============================================================================
/*
*/
class ProgramChangesComponent  : public juce::Component, public juce::Button::Listener, juce::Timer
{
private:    // fields
    juce::OwnedArray<juce::TextButton> m_programChanceTiles;
    TilesLookAndFeed    m_tilesLookAndFeel;
    int m_horizontalOffset = 0;
    std::unique_ptr<ValueAnimator> m_valueAnimatorPtr;

private:    // implementation
    virtual void buttonClicked(juce::Button* pButton) override;

    void timerCallback() override;
    void startTileAnimation(int endValue);

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

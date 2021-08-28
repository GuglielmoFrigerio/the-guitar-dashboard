/*
  ==============================================================================

    ProgramChangesComponent.cpp
    Created: 27 Aug 2021 4:08:02pm
    Author:  gugli

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ProgramChangesComponent.h"
#include "Track.h"
#include "GuitarDashCommon.h"

void ProgramChangesComponent::buttonClicked(juce::Button* pButton)
{
    auto idAsString = pButton->getComponentID();
    auto index = idAsString.getIntValue();

    if (onProgramChangeSelected != nullptr)
        onProgramChangeSelected(index);
}

//==============================================================================
ProgramChangesComponent::ProgramChangesComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

ProgramChangesComponent::~ProgramChangesComponent()
{
}

void ProgramChangesComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("ProgramChangesComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void ProgramChangesComponent::resized()
{
    auto bounds = getLocalBounds();
    computeFlexBox(120, 60, bounds.getWidth(), m_programChanceTiles.size(), [this](int index, int x, int y, int w, int h) {
        m_programChanceTiles[index]->setBounds(x, y, w, h);
    });
}

void ProgramChangesComponent::update(const Track* pTrack)
{
    for (auto index = 0; index < m_programChanceTiles.size(); ++index) {
        removeChildComponent(m_programChanceTiles[index]);
    }
    m_programChanceTiles.clear(true);

    pTrack->enumerateProgramChanges([this](const ProgramChangeEvent* pProgramChangeEvent, int index) {
        auto tooltip = juce::String::formatted("%d.%d", pProgramChangeEvent->programChange.programNumber, pProgramChangeEvent->programChange.sceneNumber);
        auto pNewTextButton = new juce::TextButton(pProgramChangeEvent->programChange.name, tooltip);
        pNewTextButton->addListener(this);
        pNewTextButton->setComponentID(juce::String(index));
        addAndMakeVisible(m_programChanceTiles.add(pNewTextButton));
    });

    resized();

    if (m_programChanceTiles.size() > 0) {
        if (onProgramChangeSelected != nullptr)
            onProgramChangeSelected(0);
    }
}

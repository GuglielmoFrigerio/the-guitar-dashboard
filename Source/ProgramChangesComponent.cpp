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

const int TileWidth = 270;
const int TileHeight = 135;

void ProgramChangesComponent::buttonClicked(juce::Button* pButton)
{
    if (pButton->getToggleState()) {
        auto idAsString = pButton->getComponentID();
        auto index = idAsString.getIntValue();

        if (onProgramChangeSelected != nullptr)
            onProgramChangeSelected(index);

        slideTiles(index);
    }
}

void ProgramChangesComponent::timerCallback()
{
    if (!m_valueAnimatorPtr->timerCallback()) {
        m_valueAnimatorPtr = nullptr;
        stopTimer();
    }
}

void ProgramChangesComponent::startTileAnimation(int endValue)
{
    auto timerMustStart = m_valueAnimatorPtr == nullptr;
    m_valueAnimatorPtr = std::make_unique<ValueAnimator>(m_horizontalOffset, endValue, 30);
    m_valueAnimatorPtr->onNewValue = [this](int newValue) {
        m_horizontalOffset = newValue;
        resized();
    };
    if (timerMustStart)
        startTimer(17);
}

void ProgramChangesComponent::slideTiles(int selectedIndex)
{
    auto bounds = getLocalBounds();
    auto tileCenter = selectedIndex * TileWidth + TileWidth / 2;
    auto xCenter = bounds.getWidth() / 2;
    auto horizontalOffset = 0;
    if (tileCenter > xCenter) {
        horizontalOffset = tileCenter - xCenter;
        auto xLeft = m_programChanceTiles.size() * TileWidth - tileCenter;
        if (xLeft < xCenter)
            horizontalOffset -= (xCenter - xLeft);
    }
    if (horizontalOffset != m_horizontalOffset) {
        startTileAnimation(horizontalOffset);
    }
}

//==============================================================================
ProgramChangesComponent::ProgramChangesComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setLookAndFeel(&m_tilesLookAndFeel);
}

ProgramChangesComponent::~ProgramChangesComponent()
{
    setLookAndFeel(nullptr);
}

void ProgramChangesComponent::paint (juce::Graphics& g)
{
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
    auto x = -m_horizontalOffset;
    auto y = bounds.getHeight() / 2 - (TileHeight / 2);
    for (auto pTile : m_programChanceTiles) {
        pTile->setBounds(x, y, TileWidth, TileHeight);
        x += TileWidth;
    }
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
        pNewTextButton->setClickingTogglesState(true);
        pNewTextButton->setRadioGroupId(ProgramChangesButtons);
        pNewTextButton->addListener(this);
        pNewTextButton->setComponentID(juce::String(index));
        addAndMakeVisible(m_programChanceTiles.add(pNewTextButton));
    });

    resized();

    if (m_programChanceTiles.size() > 0) {
        selectProgramChange(0);
    }
}

void ProgramChangesComponent::selectProgramChange(int programChangeIndex)
{
    if (programChangeIndex < m_programChanceTiles.size()) {
        m_programChanceTiles[programChangeIndex]->triggerClick();
    }
}

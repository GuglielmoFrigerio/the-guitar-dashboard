/*
  ==============================================================================

    VirtualBandPage.cpp
    Created: 14 Aug 2021 10:48:50am
    Author:  gugli

  ==============================================================================
*/

#include "VirtualBandPage.h"

VirtualBandPage::VirtualBandPage()
{
    addAndMakeVisible(m_midiInputList);
    addAndMakeVisible(m_midiOutputList);

    m_virtualBandPtr = std::make_unique<VirtualBand>();
    m_virtualBandPtr->loadDevices();
}

void VirtualBandPage::resized()
{
    auto rect = getLocalBounds();

    auto inputRect = rect.removeFromLeft(proportionOfWidth(0.5f));
    m_midiInputList.setBounds(inputRect);
    m_midiOutputList.setBounds(rect);
}

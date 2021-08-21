/*
  ==============================================================================

    VirtualBandPage.cpp
    Created: 14 Aug 2021 10:48:50am
    Author:  gugli

  ==============================================================================
*/

#include "VirtualBandPage.h"

void VirtualBandPage::handleProgramChange()
{
    m_virtualBandPtr->testProgramChange();
}

VirtualBandPage::VirtualBandPage()
    :   m_sendProgramChangeButton("Program Change")
{
    addAndMakeVisible(m_sendProgramChangeButton);

    m_sendProgramChangeButton.onClick = [this] { handleProgramChange(); };

    m_virtualBandPtr = std::make_unique<VirtualBand>();
    m_virtualBandPtr->loadDevices();
}

void VirtualBandPage::resized()
{
    auto rect = getLocalBounds();
    m_sendProgramChangeButton.setBounds(rect.removeFromTop(24));
}

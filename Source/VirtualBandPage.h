/*
  ==============================================================================

    VirtualBandPage.h
    Created: 14 Aug 2021 10:48:50am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <memory>
#include "Page.h"
#include "VirtualBand.h"

class VirtualBandPage : public Page
{
private:    // fields
    std::unique_ptr<VirtualBand> m_virtualBandPtr;

};

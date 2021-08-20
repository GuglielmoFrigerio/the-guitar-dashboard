/*
  ==============================================================================

    ProgramChange.cpp
    Created: 14 Aug 2021 9:54:12am
    Author:  gugli

  ==============================================================================
*/

#include "GuitarDashCommon.h"
#include "ProgramChange.h"

ProgramChange::ProgramChange(int programNumber, int sceneNumber, const juce::String& name)
    : programNumber(programNumber), sceneNumber(sceneNumber), name(name)
{
}

ProgramChange ProgramChange::parse(const juce::XmlElement* pPatchElement)
{
    auto programNumber = getElementValueAsInt(pPatchElement);
    auto sceneNumber = pPatchElement->getIntAttribute("scene");
    auto name = pPatchElement->getStringAttribute("name");
    return ProgramChange(programNumber, sceneNumber, name);
}

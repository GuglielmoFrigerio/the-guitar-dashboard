/*
  ==============================================================================

    VirtualBand.cpp
    Created: 14 Aug 2021 10:37:58am
    Author:  gugli

  ==============================================================================
*/

#include "VirtualBand.h"
#include "GuitarDashCommon.h"

void VirtualBand::loadDevices()
{
    juce::Thread::launch([this]() {
        m_fractalDevices = FractalDevice::loadAvailableDevices();
    });
}

void VirtualBand::loadSongLibrary(const juce::File& inputFile)
{
    juce::XmlDocument configDocument(inputFile);

    auto rootElementPtr = configDocument.getDocumentElement();

    auto pLibraryElement = getChildWithAttribute(rootElementPtr.get(), "name", "Agosto 2021");

    m_songCollectionPtr = SongCollection::loadFromLibraryElement(pLibraryElement, this);
}

MidiDevice* VirtualBand::getDevice(FractalDeviceType deviceType) const
{
    return nullptr;
}


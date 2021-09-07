/*
  ==============================================================================

    VirtualBand.cpp
    Created: 14 Aug 2021 10:37:58am
    Author:  gugli

  ==============================================================================
*/

#include "VirtualBand.h"
#include "GuitarDashCommon.h"
#include "SongListComponent.h"

void VirtualBand::changeListenerCallback(juce::ChangeBroadcaster* source)
{
}

VirtualBand::VirtualBand()
{
    m_formatManager.registerBasicFormats();
    m_transportSource.addChangeListener(this);   // [2]
}

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
    for (auto& fractalDevicePtr : m_fractalDevices)
    {
        auto dt = fractalDevicePtr->getDeviceType();
        if (dt == deviceType)
            return fractalDevicePtr.get();
    }
    return nullptr;
}

void VirtualBand::updateSongList(SongListComponent* pSongListComponent)
{
    pSongListComponent->update(m_songCollectionPtr.get());
}

void VirtualBand::updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent)
{
    m_songCollectionPtr->updateProgramChangesList(pProgramChangesComponent);
}

void VirtualBand::activateSong(int songIndex)
{
    m_songCollectionPtr->activateSong(songIndex, &m_formatManager, &m_transportSource);
}

void VirtualBand::selectProgramChange(int programChangeIndex)
{
    m_songCollectionPtr->selectProgramChange(programChangeIndex);
}

void VirtualBand::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    m_transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void VirtualBand::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    m_transportSource.getNextAudioBlock(bufferToFill);
}

Song* VirtualBand::getActiveSong() const
{
    if (m_songCollectionPtr != nullptr) {
        return m_songCollectionPtr->getActiveSong();
    }
    return nullptr;
}

void VirtualBand::play()
{
    m_transportSource.start();
}


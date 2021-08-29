/*
  ==============================================================================

    TheLambsSong.cpp
    Created: 21 Aug 2021 7:04:54pm
    Author:  gugli

  ==============================================================================
*/

#include "TheLambsSong.h"
#include "MidiTrack.h"
#include "VirtualBand.h"


TheLambsSong::TheLambsSong(const juce::XmlElement* pPatchesElement, const VirtualBand* pVirtualBand)
    :   Song(pPatchesElement->getStringAttribute("name"))
{
    auto pMidiDevice = pVirtualBand->getDevice(FractalDeviceType::AxeFxIII);
    auto track = MidiTrack::loadFromPatchesElement(pPatchesElement, pMidiDevice);
    m_pMidiTrack = dynamic_cast<MidiTrack*>(track.get());
    addTrack(std::move(track));
}

void TheLambsSong::activate()
{
    selectProgramChange(0);
}

void TheLambsSong::selectProgramChange(int programChangeIndex)
{
    if (m_pMidiTrack != nullptr) {
        m_pMidiTrack->play(programChangeIndex);
        m_currentProgramIndex = programChangeIndex;
    } else {
        DBG("[TheLambsSong::selectProgramChange] Missing MidiTrack pointer");
    }
}

void TheLambsSong::updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent)
{
    if (m_pMidiTrack != nullptr)
        pProgramChangesComponent->update(m_pMidiTrack);
}

void TheLambsSong::nextMarker()
{
    if (m_pMidiTrack != nullptr) {
        if (m_currentProgramIndex < (m_pMidiTrack->getEventCount() - 1)) {
            m_currentProgramIndex++;
            m_pMidiTrack->play(m_currentProgramIndex);
        }
    }
}

void TheLambsSong::previousMarker()
{
    if (m_pMidiTrack != nullptr)
    {
        if (m_currentProgramIndex > 0) {
            m_currentProgramIndex--;
            m_pMidiTrack->play(m_currentProgramIndex);
        }
    }
}

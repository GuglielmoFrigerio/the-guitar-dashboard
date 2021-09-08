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
#include "PlayerComponent.h"


TheLambsSong::TheLambsSong(const juce::XmlElement* pPatchesElement, const VirtualBand* pVirtualBand)
    :   Song(pPatchesElement->getStringAttribute("name"))
{
    auto pMidiDevice = pVirtualBand->getDevice(FractalDeviceType::AxeFxIII);
    auto track = MidiTrack::loadFromPatchesElement(pPatchesElement, pMidiDevice);
    m_pMidiTrack = dynamic_cast<MidiTrack*>(track.get());
    addTrack(std::move(track));

    auto pTrackElement = pPatchesElement->getChildByName("Track");
    if (pTrackElement != nullptr) {
        m_trackName = pTrackElement->getStringAttribute("name");
    }
}

void TheLambsSong::activate(juce::AudioFormatManager* pAudioFormatManager, juce::AudioTransportSource* pAudioTransportSource, PlayerComponent* pPlayerComponent)
{
    if (!m_trackName.isEmpty()) {
        auto currentDir = juce::File::getCurrentWorkingDirectory();
        auto trackPath = "../../Resources/Tracks/" + m_trackName;
        auto file = currentDir.getChildFile(trackPath);
        if (file != juce::File{}) {
            auto* pReader = pAudioFormatManager->createReaderFor(file);

            if (pReader != nullptr) {
                auto newSourcePtr = std::make_unique<juce::AudioFormatReaderSource>(pReader, true);
                pAudioTransportSource->setSource(newSourcePtr.get(), 0, nullptr, pReader->sampleRate);
                m_readerSourcePtr.reset(newSourcePtr.release());
                auto duration = pAudioTransportSource->getLengthInSeconds();
                pPlayerComponent->setTrackDuration((float)duration);
            }
        }
    }
}

void TheLambsSong::selectProgramChange(int programChangeIndex)
{
    if (m_pMidiTrack != nullptr) {
        m_pMidiTrack->play(programChangeIndex);
        m_selectedProgramIndex = programChangeIndex;
    } else {
        DBG("[TheLambsSong::selectProgramChange] Missing MidiTrack pointer");
    }
}

void TheLambsSong::updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent)
{
    if (m_pMidiTrack != nullptr)
        pProgramChangesComponent->update(m_pMidiTrack);
}

std::tuple<int, int> TheLambsSong::getSelectedProgramInfo() const
{
    auto eventCount = (m_pMidiTrack != nullptr) ? m_pMidiTrack->getEventCount() : 0;
    return std::make_tuple(m_selectedProgramIndex, eventCount);
}

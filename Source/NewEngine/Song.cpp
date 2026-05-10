#include "Song.h"

namespace ne {

    namespace {
        double parseTimeString(const juce::String& s)
        {
            auto parts = juce::StringArray::fromTokens(s.trim(), ":", "");
            const auto count = parts.size();
            if (count == 3)
                return parts[0].getDoubleValue() * 3600.0
                     + parts[1].getDoubleValue() * 60.0
                     + parts[2].getDoubleValue();
            if (count == 2)
                return parts[0].getDoubleValue() * 60.0
                     + parts[1].getDoubleValue();
            if (count == 1)
                return parts[0].getDoubleValue();
            return 0.0;
        }
    }

    Song::Song(juce::String name,
               juce::String audioRelativePath,
               double bpm,
               std::vector<double> markersInSeconds,
               std::vector<Patch> patches)
        : m_name(std::move(name))
        , m_audioRelativePath(std::move(audioRelativePath))
        , m_bpm(bpm)
        , m_markersInSeconds(std::move(markersInSeconds))
        , m_patches(std::move(patches))
    {
    }

    std::unique_ptr<Song> Song::loadFromXml(const juce::XmlElement* pSongElement)
    {
        if (pSongElement == nullptr)
            return nullptr;

        const auto name = pSongElement->getStringAttribute("name");
        const auto bpm = pSongElement->getDoubleAttribute("bpm", 120.0);

        juce::String audioRelativePath;
        std::vector<double> markers;
        if (auto* pTrackElement = pSongElement->getChildByName("Track"))
        {
            audioRelativePath = "Tracks/" + pTrackElement->getStringAttribute("name");
            for (auto* pMarkerElement : pTrackElement->getChildWithTagNameIterator("Marker"))
                markers.push_back(parseTimeString(pMarkerElement->getAllSubText()));
        }

        std::vector<Patch> patches;
        for (auto* pPatchElement : pSongElement->getChildWithTagNameIterator("Patch"))
        {
            Patch patch;
            patch.name = pPatchElement->getStringAttribute("name");
            patch.scene = pPatchElement->getIntAttribute("scene");
            patch.message = pPatchElement->getStringAttribute("message");
            patch.programNumber = pPatchElement->getAllSubText().trim().getIntValue();
            patches.push_back(std::move(patch));
        }

        return std::make_unique<Song>(name,
                                      audioRelativePath,
                                      bpm,
                                      std::move(markers),
                                      std::move(patches));
    }

}

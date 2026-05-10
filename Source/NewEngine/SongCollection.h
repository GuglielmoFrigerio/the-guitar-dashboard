#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <JuceHeader.h>
#include "Song.h"

namespace ne {

    class SongCollection {
    public:
        SongCollection() = default;

        static std::unique_ptr<juce::XmlElement> loadConfigXml();
        static std::vector<juce::String> getLibraryNames(const juce::XmlElement* pConfigRoot);
        static std::unique_ptr<SongCollection> loadFromLibraryElement(const juce::XmlElement* pLibraryElement);

        int getCount() const { return static_cast<int>(m_songs.size()); }
        const Song* getSong(int index) const;
        void enumerate(std::function<void(const Song*, int)> callback) const;

    private:
        std::vector<std::unique_ptr<Song>> m_songs;
    };

}

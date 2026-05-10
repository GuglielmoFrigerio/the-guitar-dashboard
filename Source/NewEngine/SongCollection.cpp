#include "SongCollection.h"

namespace ne {

    std::unique_ptr<juce::XmlElement> SongCollection::loadConfigXml()
    {
        auto exeFolder = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory();
        auto configFile = exeFolder.getChildFile("../../../../../Configuration/Focused.xml");
        if (!configFile.existsAsFile())
        {
            DBG("ne::SongCollection: config file not found at " << configFile.getFullPathName());
            return nullptr;
        }
        juce::XmlDocument doc(configFile);
        return doc.getDocumentElement();
    }

    std::vector<juce::String> SongCollection::getLibraryNames(const juce::XmlElement* pConfigRoot)
    {
        std::vector<juce::String> names;
        if (pConfigRoot == nullptr)
            return names;
        for (auto* pLibraryElement : pConfigRoot->getChildWithTagNameIterator("Library"))
            names.push_back(pLibraryElement->getStringAttribute("name"));
        return names;
    }

    std::unique_ptr<SongCollection> SongCollection::loadFromLibraryElement(const juce::XmlElement* pLibraryElement)
    {
        auto collection = std::make_unique<SongCollection>();
        if (pLibraryElement == nullptr)
            return collection;
        for (auto* pSongElement : pLibraryElement->getChildWithTagNameIterator("Song"))
        {
            auto song = Song::loadFromXml(pSongElement);
            if (song != nullptr)
                collection->m_songs.push_back(std::move(song));
        }
        return collection;
    }

    const Song* SongCollection::getSong(int index) const
    {
        if (index < 0 || index >= static_cast<int>(m_songs.size()))
            return nullptr;
        return m_songs[index].get();
    }

    void SongCollection::enumerate(std::function<void(const Song*, int)> callback) const
    {
        int index = 0;
        for (const auto& songPtr : m_songs)
            callback(songPtr.get(), index++);
    }

}

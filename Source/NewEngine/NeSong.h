#pragma once
#include <vector>
#include <memory>
#include <JuceHeader.h>

namespace ne {

    struct Patch {
        juce::String name;
        int scene = 0;
        int programNumber = 0;
        juce::String message;
    };

    class Song {
    public:
        Song(juce::String name,
             juce::String audioRelativePath,
             double bpm,
             std::vector<double> markersInSeconds,
             std::vector<Patch> patches);

        const juce::String& getName() const { return m_name; }
        const juce::String& getAudioRelativePath() const { return m_audioRelativePath; }
        double getBpm() const { return m_bpm; }
        const std::vector<double>& getMarkers() const { return m_markersInSeconds; }
        const std::vector<Patch>& getPatches() const { return m_patches; }

        static std::unique_ptr<Song> loadFromXml(const juce::XmlElement* pSongElement);

    private:
        juce::String m_name;
        juce::String m_audioRelativePath;
        double m_bpm;
        std::vector<double> m_markersInSeconds;
        std::vector<Patch> m_patches;
    };

}

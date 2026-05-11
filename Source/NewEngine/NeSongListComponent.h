#pragma once
#include <functional>
#include <JuceHeader.h>
#include "../TilesLookAndFeel.h"

namespace ne {

    class SongCollection;

    class SongListComponent : public juce::Component,
                              public juce::Button::Listener {
    public:
        SongListComponent();
        ~SongListComponent() override;

        void paint(juce::Graphics&) override;
        void resized() override;

        void update(const SongCollection* pSongCollection);
        void selectSong(int index);

        std::function<void(int)> onSongSelected;

    private:
        void buttonClicked(juce::Button* pButton) override;

        juce::OwnedArray<juce::TextButton> m_songTiles;
        TilesLookAndFeed m_tilesLookAndFeel;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SongListComponent)
    };

}

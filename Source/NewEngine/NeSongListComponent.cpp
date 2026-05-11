#include "NeSongListComponent.h"
#include "NeSongCollection.h"
#include "NeSong.h"
#include "../GuitarDashCommon.h"

namespace {
    const int TileWidth = 270;
    const int TileHeight = 100;
    const int SongButtonsRadioGroup = 2002;
}

namespace ne {

    SongListComponent::SongListComponent()
    {
        setLookAndFeel(&m_tilesLookAndFeel);
    }

    SongListComponent::~SongListComponent()
    {
        setLookAndFeel(nullptr);
    }

    void SongListComponent::paint(juce::Graphics& g)
    {
        g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
        g.setColour(juce::Colours::grey);
        g.drawRect(getLocalBounds(), 1);
    }

    void SongListComponent::resized()
    {
        auto bounds = getLocalBounds();
        computeFlexBox(TileWidth, TileHeight, bounds.getWidth(), m_songTiles.size(),
            [this](int index, int x, int y, int w, int h) {
                m_songTiles[index]->setBounds(x, y, w, h);
            });
    }

    void SongListComponent::buttonClicked(juce::Button* pButton)
    {
        if (pButton->getToggleState())
        {
            auto index = pButton->getComponentID().getIntValue();
            if (onSongSelected != nullptr)
                onSongSelected(index);
        }
    }

    void SongListComponent::update(const SongCollection* pSongCollection)
    {
        for (auto index = 0; index < m_songTiles.size(); ++index)
            removeChildComponent(m_songTiles[index]);
        m_songTiles.clear(true);

        if (pSongCollection == nullptr)
        {
            resized();
            return;
        }

        pSongCollection->enumerate([this](const Song* pSong, int index) {
            auto pNewTextButton = new juce::TextButton(pSong->getName());
            pNewTextButton->setClickingTogglesState(true);
            pNewTextButton->setRadioGroupId(SongButtonsRadioGroup);
            pNewTextButton->addListener(this);
            pNewTextButton->setComponentID(juce::String(index));
            addAndMakeVisible(m_songTiles.add(pNewTextButton));
        });

        resized();

        if (m_songTiles.size() > 0)
            m_songTiles[0]->setToggleState(true, juce::NotificationType::sendNotification);
    }

    void SongListComponent::selectSong(int index)
    {
        if (index >= 0 && index < m_songTiles.size())
            m_songTiles[index]->triggerClick();
    }

}

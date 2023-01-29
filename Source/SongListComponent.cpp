/*
  ==============================================================================

    SongListComponent.cpp
    Created: 26 Aug 2021 3:17:08pm
    Author:  gugli

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SongListComponent.h"
#include "SongCollection.h"
#include "Song.h"
#include "GuitarDashCommon.h"

const int TileWidth = 270;
const int TileHeight = 100;


void SongListComponent::buttonClicked(juce::Button* pButton)
{
    if (pButton->getToggleState()) {
        auto idAsString = pButton->getComponentID();
        auto index = idAsString.getIntValue();

        if (onSongSelected != nullptr)
            onSongSelected(index);
    }
}

//==============================================================================
SongListComponent::SongListComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setLookAndFeel(&m_tilesLookAndFeel);

}

SongListComponent::~SongListComponent()
{
    setLookAndFeel(nullptr);
}

void SongListComponent::paint(juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    g.drawText("SongListComponent", getLocalBounds(),
        juce::Justification::centred, true);   // draw some placeholder text
}

void SongListComponent::resized()
{
    auto bounds = getLocalBounds();
    computeFlexBox(TileWidth, TileHeight, bounds.getWidth(), m_songTiles.size(), [this](int index, int x, int y, int w, int h) {
        m_songTiles[index]->setBounds(x, y, w, h);
    });
}

void SongListComponent::update(const SongCollection* pSongCollection)
{
    for (auto index = 0; index < m_songTiles.size(); ++index) {
        removeChildComponent(m_songTiles[index]);
    }
    m_songTiles.clear(true);

    pSongCollection->enumerateSongs([this](const Song* pSong, int index) {
        auto pNewTextButton = new juce::TextButton(pSong->getName());
        pNewTextButton->setClickingTogglesState(true);
        pNewTextButton->setRadioGroupId(SongButtons);
        pNewTextButton->addListener(this);
        pNewTextButton->setComponentID(juce::String(index));
        addAndMakeVisible(m_songTiles.add(pNewTextButton));
    });

    resized();

    if (m_songTiles.size() > 0) {
        m_songTiles[0]->setToggleState(true, juce::NotificationType::sendNotification);
    }
}

void SongListComponent::selectSong(int songIndex)
{
    if (songIndex < m_songTiles.size()) {
        m_songTiles[songIndex]->triggerClick();
    }
}

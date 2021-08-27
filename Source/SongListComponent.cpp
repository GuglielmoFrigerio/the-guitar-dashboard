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

void SongListComponent::buttonClicked(juce::Button* pButton)
{
    auto idAsString = pButton->getComponentID();
    auto index = idAsString.getIntValue();

    if (onSongSelected != nullptr)
        onSongSelected(index);
}

//==============================================================================
SongListComponent::SongListComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SongListComponent::~SongListComponent()
{
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
    auto buttonSize = bounds.getWidth() / 3;

    for (int i = 0; i < m_songTiles.size(); ++i)
    {
        m_songTiles[i]->setBounds(buttonSize * (i % 3),
            buttonSize * (i / 3) + bounds.getHeight() / 3,
            buttonSize,
            buttonSize);
    }
}

void SongListComponent::update(const SongCollection* pSongCollection)
{
    pSongCollection->enumerateSongs([this](const Song* pSong, int index) {
        auto pNewTextButton = new juce::TextButton(pSong->getName());
        pNewTextButton->addListener(this);
        pNewTextButton->setComponentID(juce::String(index));
        addAndMakeVisible(m_songTiles.add(pNewTextButton));
    });

    if (m_songTiles.size() > 0) {
        if (onSongSelected != nullptr)
            onSongSelected(0);
    }
}

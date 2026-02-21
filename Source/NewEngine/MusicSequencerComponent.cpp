/*
  ==============================================================================

    MusicSequencerComponent.cpp
    Created: 2 Feb 2026 1:55:35pm
    Author:  frigeriog-adm

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MusicSequencerComponent.h"

//==============================================================================
MusicSequencerComponent::MusicSequencerComponent()
{
    setAudioChannels(2, 2);
}

MusicSequencerComponent::~MusicSequencerComponent()
{
}

void MusicSequencerComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("MusicSequencerComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void MusicSequencerComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void MusicSequencerComponent::releaseResources()
{
}

void MusicSequencerComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
}

void MusicSequencerComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
}

/*
  ==============================================================================

    MusicSequencerComponent.cpp
    Created: 2 Feb 2026 1:55:35pm
    Author:  frigeriog-adm

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MusicSequencerComponent.h"

constexpr double kDefaultBpm = 120.0;

//==============================================================================
MusicSequencerComponent::MusicSequencerComponent()
	: m_musicSequencer(kDefaultBpm)
{
    // --- BPM Slider setup ---
    m_bpmSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    m_bpmSlider.setRange(40.0, 208.0, 1.0);   // min, max, step
    m_bpmSlider.setValue(120.0);               // default BPM
    m_bpmSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);
    m_bpmSlider.addListener(this);
    addAndMakeVisible(m_bpmSlider);

    // --- Label setup ---
    m_bpmLabel.setText("BPM", juce::dontSendNotification);
    m_bpmLabel.attachToComponent(&m_bpmSlider, true); // true = label on the left
    addAndMakeVisible(m_bpmLabel);

    addAndMakeVisible(m_playerComponent);

    setAudioChannels(2, 2);
}

MusicSequencerComponent::~MusicSequencerComponent()
{
    shutdownAudio();
    m_bpmSlider.removeListener(this);
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
    auto area = getLocalBounds();

    // Carve out the bottom-left region
    // Adjust width/height to taste
    const int sliderWidth = 250;
    const int sliderHeight = 40;
    const int labelWidth = 40; // space reserved for the attached label
    const int margin = 10;

    m_bpmSlider.setBounds(
        margin + labelWidth,                          // x  (offset for label)
        area.getHeight() - sliderHeight - margin,     // y  (bottom)
        sliderWidth,                                  // width
        sliderHeight                                  // height
    );

    m_playerComponent.setBounds(area.removeFromBottom(160));

}

void MusicSequencerComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &m_bpmSlider)
    {
        double bpm = m_bpmSlider.getValue();
		m_musicSequencer.uiSetTempo(bpm);
    }   
}

void MusicSequencerComponent::releaseResources()
{
}

void MusicSequencerComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	m_musicSequencer.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MusicSequencerComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	m_musicSequencer.getNextAudioBlock(bufferToFill);
}

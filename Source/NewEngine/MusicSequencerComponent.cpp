/*
  ==============================================================================

    MusicSequencerComponent.cpp
    Created: 2 Feb 2026 1:55:35pm
    Author:  frigeriog-adm

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MusicSequencerComponent.h"
#include "NeSong.h"
#include "../GuitarDashCommon.h"

constexpr double kDefaultBpm = 120.0;

//==============================================================================
MusicSequencerComponent::MusicSequencerComponent()
    : m_musicSequencer(kDefaultBpm)
{
    // --- BPM Slider setup ---
    m_bpmSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    m_bpmSlider.setRange(40.0, 208.0, 1.0);
    m_bpmSlider.setValue(kDefaultBpm);
    m_bpmSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);
    m_bpmSlider.addListener(this);
    addAndMakeVisible(m_bpmSlider);

    m_bpmLabel.setText("BPM", juce::dontSendNotification);
    m_bpmLabel.attachToComponent(&m_bpmSlider, true);
    addAndMakeVisible(m_bpmLabel);

    // --- Libraries combo box ---
    m_librariesLabel.setText("Library", juce::dontSendNotification);
    m_librariesLabel.attachToComponent(&m_librariesComboBox, true);
    addAndMakeVisible(m_librariesLabel);
    addAndMakeVisible(m_librariesComboBox);

    m_librariesComboBox.onChange = [this] {
        auto id = m_librariesComboBox.getSelectedId();
        if (id > 0)
        {
            auto libraryName = m_librariesComboBox.getItemText(id - 1);
            loadLibrary(libraryName);
        }
    };

    // --- Song list ---
    m_songListComponent.onSongSelected = [this](int songIndex) { onSongSelected(songIndex); };
    addAndMakeVisible(m_songListComponent);

    addAndMakeVisible(m_playerComponent);

    loadConfig();
    populateLibraries();

    setAudioChannels(2, 2);
}

MusicSequencerComponent::~MusicSequencerComponent()
{
    shutdownAudio();
    m_bpmSlider.removeListener(this);
}

void MusicSequencerComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
}

void MusicSequencerComponent::resized()
{
    auto area = getLocalBounds();
    const int margin = 10;
    const int comboHeight = 24;
    const int libraryLabelWidth = 80;
    const int playerHeight = 160;
    const int sliderHeight = 40;
    const int bpmLabelWidth = 40;
    const int bpmSliderWidth = 250;

    m_librariesComboBox.setBounds(
        margin + libraryLabelWidth,
        margin,
        area.getWidth() - margin * 2 - libraryLabelWidth,
        comboHeight
    );

    m_playerComponent.setBounds(0, area.getHeight() - playerHeight, area.getWidth(), playerHeight);

    m_bpmSlider.setBounds(
        margin + bpmLabelWidth,
        area.getHeight() - playerHeight - sliderHeight - margin,
        bpmSliderWidth,
        sliderHeight
    );

    const int songListTop = margin + comboHeight + margin;
    const int songListBottom = area.getHeight() - playerHeight - sliderHeight - margin * 2;
    m_songListComponent.setBounds(
        margin,
        songListTop,
        area.getWidth() - margin * 2,
        juce::jmax(0, songListBottom - songListTop)
    );
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

void MusicSequencerComponent::loadConfig()
{
    m_configElementPtr = ne::SongCollection::loadConfigXml();
}

void MusicSequencerComponent::populateLibraries()
{
    m_librariesComboBox.clear();
    if (m_configElementPtr == nullptr)
        return;

    const auto names = ne::SongCollection::getLibraryNames(m_configElementPtr.get());
    int id = 1;
    for (const auto& name : names)
        m_librariesComboBox.addItem(name, id++);

    if (!names.empty())
        m_librariesComboBox.setSelectedId(1, juce::sendNotification);
}

void MusicSequencerComponent::loadLibrary(const juce::String& libraryName)
{
    if (m_configElementPtr == nullptr)
        return;

    auto* pLibraryElement = getChildWithAttribute(m_configElementPtr.get(), "name", libraryName);
    m_songCollectionPtr = ne::SongCollection::loadFromLibraryElement(pLibraryElement);
    m_songListComponent.update(m_songCollectionPtr.get());
}

void MusicSequencerComponent::onSongSelected(int songIndex)
{
    if (m_songCollectionPtr == nullptr)
        return;
    auto* pSong = m_songCollectionPtr->getSong(songIndex);
    if (pSong == nullptr)
        return;
    DBG("ne::MusicSequencerComponent: song selected: " << pSong->getName()
        << " audio: " << pSong->getAudioRelativePath());
    // Phase 1.c will swap the AudioTrack buffer here.
}

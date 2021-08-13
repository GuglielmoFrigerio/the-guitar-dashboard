#include "MainComponent.h"


const int MaxInputChannels = 32;


//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(m_openSettings);
    m_openSettings.setButtonText("Open Settings");

    addAndMakeVisible(m_closeSettings);
    m_closeSettings.setButtonText("Close Settings");

    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 6 : 0, 6); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (6, 6);
    }

    deviceManager.addChangeListener(this);
    m_openSettings.addListener(this);
    m_closeSettings.addListener(this);
    addKeyListener(this);

    startTimer(50);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()

    m_osc1Ptr = std::make_unique<Oscillator>(sampleRate, 440.0);
    m_osc2Ptr = std::make_unique<Oscillator>(sampleRate, 660.0);
    m_lfo = std::make_unique<Lfo>(sampleRate, 1.0);
    m_pitchDetector = std::make_unique<PitchDetector>(sampleRate, 0.001);
    chooseInputChannelIndex();
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* device = deviceManager.getCurrentAudioDevice();
    auto activeInputChannels = device->getActiveInputChannels();
    auto maxInputChannels = activeInputChannels.getHighestBit() + 1;

    auto activeOutputChannels = device->getActiveOutputChannels();
    auto maxOutputChannels = activeOutputChannels.countNumberOfSetBits();

    //for (auto channel = 0; channel < maxOutputChannels; ++channel)
    //{
    //    if ((!activeOutputChannels[channel]) || maxInputChannels == 0)
    //    {
    //        bufferToFill.buffer->clear(channel, bufferToFill.startSample, bufferToFill.numSamples);
    //    }
    //    else
    //    {
    //        auto actualInputChannel = channel % maxInputChannels; // [1]

    //        if (!activeInputChannels[channel]) // [2]
    //        {
    //            bufferToFill.buffer->clear(channel, bufferToFill.startSample, bufferToFill.numSamples);
    //        }
    //        else // [3]
    //        {
    //            auto* inBuffer = bufferToFill.buffer->getReadPointer(actualInputChannel,
    //                bufferToFill.startSample);
    //            auto* outBuffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
    //        }
    //    }
    //}

    if (m_inputChannelIndex != -1)
    {
        auto* inBuffer = bufferToFill.buffer->getReadPointer(m_inputChannelIndex, bufferToFill.startSample);
        m_limitFollower.update(inBuffer, bufferToFill.numSamples);
        auto [noteNumber, volume] = m_pitchDetector->detectPitch(inBuffer, bufferToFill.numSamples);
        m_midiNote = noteNumber;
        if (volume != 0.f)
            m_volume = volume;
    }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    auto rect = getLocalBounds();
    auto buttonsSize = rect.removeFromTop(20);
    auto right = buttonsSize.removeFromLeft(rect.getWidth() / 2);
    m_openSettings.setBounds(right);
    m_closeSettings.setBounds(buttonsSize);
    if (m_setupPagePtr != nullptr)
    {
        m_setupPagePtr->setBounds(rect);
    }

}

void MainComponent::timerCallback()
{
    static int timerCounter = 0;

    if (++timerCounter % 20 == 0)
    {
        auto message = juce::String::formatted("lower limit: %g, upper limit: %g, sum: %g, midiNote: %d, volume: %g", m_limitFollower.getLower(), m_limitFollower.getHigher(), m_sum, m_midiNote, m_volume);
        //logMessage(message);
    }

    //auto cpu = deviceManager.getCpuUsage() * 100;
    //cpuUsageText.setText(juce::String(cpu, 6) + " %", juce::dontSendNotification);
}

void MainComponent::changeListenerCallback(juce::ChangeBroadcaster*)
{
    //dumpDeviceInfo();
    m_limitFollower.reset();
    auto* device = deviceManager.getCurrentAudioDevice();

    chooseInputChannelIndex();
}

void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &m_openSettings) 
    {
        m_setupPagePtr = std::make_unique<SetupPage>(deviceManager);
        addAndMakeVisible(m_setupPagePtr.get());
        resized();
    } else {
        removeChildComponent(m_setupPagePtr.get());
        m_setupPagePtr = nullptr;
        resized();
    }    
}

void MainComponent::chooseInputChannelIndex()
{
    auto* device = deviceManager.getCurrentAudioDevice();
    auto activeInputChannels = device->getActiveInputChannels();
    m_inputChannelIndex = activeInputChannels[m_preferredInputChannelIndex] ? m_preferredInputChannelIndex : 0;
}

bool MainComponent::keyPressed(const juce::KeyPress& key, juce::Component* originatingComponent)
{
    return false;
}

/*
  ==============================================================================

    AudioRecorder.h
    Created: 4 Jun 2023 11:51:09am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class AudioRecorder : public juce::AudioIODeviceCallback {
private:
    juce::TimeSliceThread m_backgroundThread{ "Audio Recorder Thread" }; // the thread that will write our audio data to disk
    double m_sampleRate = 0.0;
    std::unique_ptr<juce::AudioFormatWriter::ThreadedWriter> m_threadedWriter; // the FIFO used to buffer the incoming data
    juce::CriticalSection m_writerLock;
    std::atomic<juce::AudioFormatWriter::ThreadedWriter*> m_activeWriter { nullptr };
    int m_numChannels = 0;
    juce::File m_recordFolder;

private:    // implementation
    juce::File getFilename(const juce::String& folderName)
    {
        time_t rawtime;
        struct tm* timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, 80, "%Y.%m.%d_%H_%M_%S.wav", timeinfo);

        auto folder = m_recordFolder.getChildFile(folderName);
        folder.createDirectory();

        return folder.getChildFile(buffer);
    }

private: //AudioIODeviceCallback overrides
    void audioDeviceAboutToStart(juce::AudioIODevice* device) override
    {
        m_sampleRate = device->getCurrentSampleRate();
    }

    void audioDeviceStopped() override
    {
        m_sampleRate = 0.0;
    }

public: // public interface
    AudioRecorder(const juce::String& resourcePath) {
        m_backgroundThread.startThread();
        auto resourceRoot = juce::File::getCurrentWorkingDirectory().getChildFile(resourcePath);

        m_recordFolder = resourceRoot.getChildFile("recordings/audio");
        m_recordFolder.createDirectory();
    }

    void startRecording(const juce::String& folderName)
    {
        stop();

        auto file = getFilename(folderName);

        if (m_sampleRate > 0)
        {
            // Create an OutputStream to write to our destination file...
            file.deleteFile();

            if (auto fileStream = std::unique_ptr<juce::FileOutputStream>(file.createOutputStream()))
            {
                // Now create a WAV writer object that writes to our output stream...
                juce::WavAudioFormat wavFormat;

                if (auto writer = wavFormat.createWriterFor(fileStream.get(), m_sampleRate, 2, 24, {}, 0))
                {
                    fileStream.release(); // (passes responsibility for deleting the stream to the writer object that is now using it)

                    // Now we'll create one of these helper objects which will act as a FIFO buffer, and will
                    // write the data to disk on our background thread.
                    m_threadedWriter.reset(new juce::AudioFormatWriter::ThreadedWriter(writer, m_backgroundThread, 32768));

                    m_numChannels = writer->getNumChannels();

                    // And now, swap over our active writer pointer so that the audio callback will start using it..
                    const juce::ScopedLock sl(m_writerLock);
                    m_activeWriter = m_threadedWriter.get();
                }
            }
        }
    }

    void audioDeviceIOCallbackWithContext(const float* const* inputChannelData, int numInputChannels,
        float* const* outputChannelData, int numOutputChannels,
        int numSamples, const juce::AudioIODeviceCallbackContext& context) override
    {
        ignoreUnused(context);

        const juce::ScopedLock sl(m_writerLock);

        if (m_activeWriter.load() != nullptr && numInputChannels >= m_numChannels)
        {
            m_activeWriter.load()->write(inputChannelData, numSamples);
        }

        // We need to clear the output buffers, in case they're full of junk..
        for (int i = 0; i < numOutputChannels; ++i)
            if (outputChannelData[i] != nullptr)
                juce::FloatVectorOperations::clear(outputChannelData[i], numSamples);
    }

    void stop()
    {
        // First, clear this pointer to stop the audio callback from using our writer object..
        {
            const juce::ScopedLock sl(m_writerLock);
            m_activeWriter = nullptr;
        }

        // Now we can delete the writer object. It's done in this order because the deletion could
        // take a little time while remaining data gets flushed to disk, so it's best to avoid blocking
        // the audio callback while this happens.
        m_threadedWriter.reset();
    }
};

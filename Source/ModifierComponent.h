/*
  ==============================================================================

    ModifierComponent.h
    Created: 6 Sep 2025 2:43:42pm
    Author:  frigeriog-adm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ReadOnlySlider : public juce::Slider
{
public:
    ReadOnlySlider()
    {
        setSliderStyle(juce::Slider::LinearHorizontal);
        setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        setRange(0.0, 100.0, 1.0);
    }

    // ignore any mouse events so it becomes read-only
    void mouseDown(const juce::MouseEvent&) override {}
    void mouseDrag(const juce::MouseEvent&) override {}
    void mouseUp(const juce::MouseEvent&) override {}
};

//==============================================================================
/*
*/
class ModifierComponent  : public juce::Component
{
public:
    ModifierComponent()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        addAndMakeVisible(m_slider);
        m_slider.setRange(0.0, 127.0, 1.0);

    }

    ~ModifierComponent() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        auto color = getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId);
        if (m_currentValue >= 0)
            color = juce::Colours::darkseagreen;

        g.fillAll (color);   // clear the background

        g.setColour (juce::Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        auto rect = getLocalBounds();
        m_slider.setBounds(rect);
    }

    void updateValue(int currentValue) {
        m_currentValue = currentValue;
        if (currentValue >= 0)
            m_slider.setValue(currentValue);
        repaint();
    }

private:

    int m_currentValue = -1;
    ReadOnlySlider m_slider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModifierComponent)
};

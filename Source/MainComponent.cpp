#include "MainComponent.h"
#include "VirtualBandPage.h"


const int MaxInputChannels = 32;


//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(m_setupButton);
    m_setupButton.setButtonText("Setup");

    addAndMakeVisible(m_virtualBandButton);
    m_virtualBandButton.setButtonText("Virtual Band");

    propInit();

    m_virtualBandPagePtr = std::make_unique<VirtualBandPage>(m_properties);
    addAndMakeVisible(m_virtualBandPagePtr.get());

    // you add any child components.
    setSize (800, 600);

    m_setupButton.addListener(this);
    m_virtualBandButton.addListener(this);
}

MainComponent::~MainComponent()
{
}

//==============================================================================


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
    m_setupButton.setBounds(right);
    m_virtualBandButton.setBounds(buttonsSize);
    if (m_activePage != nullptr)
    {
        m_activePage->setBounds(rect);
    }
    else {
        m_virtualBandPagePtr->setBounds(rect);
    }

}

void MainComponent::buttonClicked(juce::Button* button)
{
    if (m_activePage != nullptr)
    {
        removeChildComponent(m_activePage.get());
        m_activePage = nullptr;
        resized();
    }
    else {
        removeChildComponent(m_virtualBandPagePtr.get());
    }

    if (button == &m_setupButton) 
    {
        m_activePage = std::make_unique<SetupPage>(m_virtualBandPagePtr->deviceManager);
    } else {
        addAndMakeVisible(m_virtualBandPagePtr.get());
    }    

    addAndMakeVisible(m_activePage.get());
    resized();
}

void MainComponent::propInit()
{
    juce::PropertiesFile::Options options;
    options.applicationName = ProjectInfo::projectName;
    options.filenameSuffix = ".settings";
    options.osxLibrarySubFolder = "Application Support";
    options.folderName = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userApplicationDataDirectory).getChildFile(ProjectInfo::projectName).getFullPathName();
    options.storageFormat = juce::PropertiesFile::storeAsXML;

    m_properties.setStorageParameters(options);
}

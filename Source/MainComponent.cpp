#include "MainComponent.h"
#include "VirtualBandPage.h"
#include "NewEngine/MusicSequencerComponent.h"


const int MaxInputChannels = 32;
static const char* UseNewEngineKey = "useNewEngine";


//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(m_setupButton);
    m_setupButton.setButtonText("Setup");

    addAndMakeVisible(m_virtualBandButton);
    m_virtualBandButton.setButtonText("Virtual Band");

    addAndMakeVisible(m_engineToggleButton);

    propInit();
    createEnginePage();

    setSize (800, 600);

    m_setupButton.addListener(this);
    m_virtualBandButton.addListener(this);
    m_engineToggleButton.addListener(this);
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
    auto buttonsRow = rect.removeFromTop(20);
    auto buttonWidth = buttonsRow.getWidth() / 3;
    m_setupButton.setBounds(buttonsRow.removeFromLeft(buttonWidth));
    m_virtualBandButton.setBounds(buttonsRow.removeFromLeft(buttonWidth));
    m_engineToggleButton.setBounds(buttonsRow);
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
    if (button == &m_engineToggleButton)
    {
        if (m_activePage != nullptr)
        {
            removeChildComponent(m_activePage.get());
            m_activePage = nullptr;
        }
        removeChildComponent(m_virtualBandPagePtr.get());
        m_virtualBandPagePtr.reset();
        setUsingNewEngine(!isUsingNewEngine());
        createEnginePage();
        resized();
        return;
    }

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

bool MainComponent::isUsingNewEngine()
{
    return m_properties.getUserSettings()->getBoolValue(UseNewEngineKey, true);
}

void MainComponent::setUsingNewEngine(bool useNewEngine)
{
    m_properties.getUserSettings()->setValue(UseNewEngineKey, useNewEngine);
    m_properties.saveIfNeeded();
}

void MainComponent::createEnginePage()
{
    const bool useNewEngine = isUsingNewEngine();
    if (useNewEngine)
        m_virtualBandPagePtr = std::make_unique<MusicSequencerComponent>();
    else
        m_virtualBandPagePtr = std::make_unique<VirtualBandPage>(m_properties);

    m_engineToggleButton.setButtonText(useNewEngine ? "Engine: New" : "Engine: Old");
    addAndMakeVisible(m_virtualBandPagePtr.get());
}

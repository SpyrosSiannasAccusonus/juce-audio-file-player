/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.8

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/


#include "Editor.h"
#include "PluginProcessor.h"

//==============================================================================
Editor::Editor (AudioPlayerAudioProcessor* p):
processor(p)
{
    juce__textButton.reset (new juce::TextButton ("file"));
    addAndMakeVisible (juce__textButton.get());
    juce__textButton->setButtonText (TRANS("select file"));
    juce__textButton->addListener (this);

    juce__textButton->setBounds (104, 56, 150, 24);

    juce__textButton2.reset (new juce::TextButton ("toggleplay"));
    addAndMakeVisible (juce__textButton2.get());
    juce__textButton2->setButtonText (TRANS("play/stop"));
    juce__textButton2->addListener (this);

    juce__textButton2->setBounds (104, 120, 150, 24);

    setSize (600, 400);
}

Editor::~Editor()
{
    juce__textButton = nullptr;
    juce__textButton2 = nullptr;
}

//==============================================================================
void Editor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour (0xff323e44));

    {
        int x = 4, y = 4, width = 364, height = 228;
        juce::Colour fillColour = juce::Colours::cadetblue;

        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }
}

void Editor::resized()
{

}

void Editor::loadFile()
{
    myChooser = std::make_unique<juce::FileChooser> ("Please select the file you want to load...",
                                                     juce::File::getSpecialLocation (juce::File::userHomeDirectory), "*.wav","*.mp3");
 
    auto folderChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;
    myChooser -> launchAsync(folderChooserFlags,  [this] (const juce::FileChooser& myChooser) {
        juce::File audioFile (myChooser.getResult());
        processor->loadAudioFile(audioFile);
        processor->audioLoaded = true;
    });
}


void Editor::buttonClicked (juce::Button* buttonThatWasClicked)
{

    if (buttonThatWasClicked == juce__textButton.get())
    {
        loadFile();
    }
    else if (buttonThatWasClicked == juce__textButton2.get())
    {
        processor->togglePlaying();
        if (processor->isPlaying)
            processor->transportSource.start();
        else
        {
            processor->transportSource.stop();
            processor->transportSource.setPosition (0.0);
        }
    }
}


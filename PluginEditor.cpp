/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PrismizerAudioProcessorEditor::PrismizerAudioProcessorEditor (PrismizerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    rawVolume.label.setText("Dry", juce::dontSendNotification);
    wetVolume.label.setText("Wet", juce::dontSendNotification);
    
    rawVolume.slider.addListener(this);
    wetVolume.slider.addListener(this);
    
    // this function adds the slider to the editor
    addAndMakeVisible(&rawVolume.slider);
    addAndMakeVisible(&wetVolume.slider);
    
}

void PrismizerAudioProcessorEditor::sliderValueChanged(juce::Slider *slider){
    audioProcessor.noteOnVel = rawVolume.slider.getValue();
}

PrismizerAudioProcessorEditor::~PrismizerAudioProcessorEditor()
{
    
}

//==============================================================================
void PrismizerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Prismizer", getLocalBounds(), juce::Justification::centred, 1);
}

void PrismizerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    
    rawVolume.slider.setBounds (40, 30, 80, getHeight() - 60);
    wetVolume.slider.setBounds (120, 30, 80, getHeight() - 60);
}

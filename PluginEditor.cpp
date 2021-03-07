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
    setSize (600, 400);
    
    
    
    //Initialization-----------------------------------------
    
    autotuneToggle.setButtonText("Autotune");
    
    fc1.setText("Follower 1");
    fc2.setText("Follower 2");
    smoothing.setText("smoothing");
    
    rawVolume.setText("Dry");
    wetVolume.setText("Wet");
    
    //listener/visibility setup------------------------------
    
    autotuneToggle.addListener(this);
    
    fc1.toggle.addListener(this);
    fc1.pitchSlider.addListener(this);
    fc2.toggle.addListener(this);
    fc2.pitchSlider.addListener(this);
    
    ADSR.attack.slider.addListener(this);
    ADSR.decay.slider.addListener(this);
    ADSR.sustain.slider.addListener(this);
    ADSR.release.slider.addListener(this);
    
    //TODO: add listener for tunerkeybaord
    
    smoothing.slider.addListener(this);
    
    rawVolume.slider.addListener(this);
    wetVolume.slider.addListener(this);
    
    //-------------------------------------------------------
    
    addAndMakeVisible(&autotuneToggle);
    addAndMakeVisible(&fc1);
    addAndMakeVisible(&fc2);
    addAndMakeVisible(&ADSR);
    addAndMakeVisible(&tKey);
    addAndMakeVisible(&smoothing);
    addAndMakeVisible(&rawVolume);
    addAndMakeVisible(&wetVolume);
    
}

//LISTENERS====================================================================

void PrismizerAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    audioProcessor.noteOnVel = rawVolume.slider.getValue();
}

void PrismizerAudioProcessorEditor::buttonClicked(juce::Button *button)
{
    DBG(button->getToggleStateValue().toString());
}

//==============================================================================

PrismizerAudioProcessorEditor::~PrismizerAudioProcessorEditor()
{
    
}

void PrismizerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void PrismizerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    autotuneToggle.setBounds(200, 30, 100, 40);
    fc1.setTopLeftPosition(rawVolume.getWidth(), rawVolume.getHeight());
    fc2.setTopLeftPosition(fc1.getX(), fc1.getHeight());
    ADSR.setTopLeftPosition(400, 0);
    tKey.setTopLeftPosition(200, 300);
    smoothing.setTopLeftPosition(400, 200);
    wetVolume.setTopLeftPosition(rawVolume.getX() + rawVolume.getWidth(), 0);
}

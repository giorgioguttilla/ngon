/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <string>

//==============================================================================
PrismizerAudioProcessorEditor::PrismizerAudioProcessorEditor (PrismizerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //timer will listen for processor pitch detection and adjust tunerkeyboard
    startTimer(100);
            
    //ValueTree pointer initializations
    
    attackValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "attack", ADSR.attack.slider);
    
    decayValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "decay", ADSR.sustain.slider);
    
    sustainValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "sustain", ADSR.sustain.slider);
    
    releaseValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "release", ADSR.release.slider);
    
    
    
    smoothingValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "smoothing", smoothing.slider);
    
    detuneValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "detune", detune.slider);

    spreadValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "spread", spread.slider);

    
    
    rawVolumeValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "rawVolume", rawVolume.slider);
    
    wetVolumeValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "wetVolume", wetVolume.slider);
    
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
    
    
    
    //Initialization-----------------------------------------

    smoothing.setText("smoothing");
    detune.setText("detune");
    spread.setText("spread");
    
    rawVolume.setText("Dry");
    wetVolume.setText("Wet");
    
    //listener/visibility setup------------------------------
    
    ADSR.attack.slider.addListener(this);
    ADSR.decay.slider.addListener(this);
    ADSR.sustain.slider.addListener(this);
    ADSR.release.slider.addListener(this);
    
    smoothing.slider.addListener(this);
    detune.slider.addListener(this);
    spread.slider.addListener(this);
    
    rawVolume.slider.addListener(this);
    wetVolume.slider.addListener(this);
    
    //-------------------------------------------------------
    

    addAndMakeVisible(&ADSR);
    addAndMakeVisible(&smoothing);
    addAndMakeVisible(&detune);
    addAndMakeVisible(&spread);
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
//    DBG(button->getToggleStateValue().toString());
}

//==============================================================================

PrismizerAudioProcessorEditor::~PrismizerAudioProcessorEditor()
{

}

//sets tunkerkeyboard target value. unset if no autotune active or no note detected
void PrismizerAudioProcessorEditor::timerCallback()
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
    ADSR.setTopLeftPosition(400, 0);
    smoothing.setTopLeftPosition(0, 200);
    detune.setTopLeftPosition(100, 200);
    spread.setTopLeftPosition(200, 200);
    wetVolume.setTopLeftPosition(rawVolume.getX() + rawVolume.getWidth(), 0);
    
}

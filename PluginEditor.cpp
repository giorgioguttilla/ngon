/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <string>
#include "PrismVoice.h"

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
    
    
    
    vibratoRateValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "vibratoRate", vibrato.rateSlider.slider);
    vibratoDepthValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "vibratoDepth", vibrato.depthSlider.slider);
    vibratoTriggerValue = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.params, "vibratoTrigger", vibrato.triggerButton);
    
    
    
    tremoloRateValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "tremoloRate", tremolo.rateSlider.slider);
    tremoloDepthValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "tremoloDepth", tremolo.depthSlider.slider);
    tremoloTriggerValue = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.params, "tremoloTrigger", tremolo.triggerButton);
    
    
    
    rawVolumeValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "rawVolume", rawVolume.slider);
    
    wetVolumeValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "wetVolume", wetVolume.slider);
    
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
    
    
    
    //Initialization-----------------------------------------

    smoothing.setText("smoothing");
    detune.setText("detune");
    spread.setText("spread");
    
    vibrato.setText("vibrato");
    tremolo.setText("tremolo");
    
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
    
    vibrato.rateSlider.slider.addListener(this);
    vibrato.depthSlider.slider.addListener(this);
    vibrato.triggerButton.addListener(this);
    
    tremolo.rateSlider.slider.addListener(this);
    tremolo.depthSlider.slider.addListener(this);
    tremolo.triggerButton.addListener(this);
    
    rawVolume.slider.addListener(this);
    wetVolume.slider.addListener(this);
    
    //-------------------------------------------------------
    
    addAndMakeVisible(&ADSR);
    addAndMakeVisible(&smoothing);
    addAndMakeVisible(&detune);
    addAndMakeVisible(&spread);
    addAndMakeVisible(&vibrato);
    addAndMakeVisible(&tremolo);
    addAndMakeVisible(&rawVolume);
    addAndMakeVisible(&wetVolume);
        
}

//LISTENERS====================================================================

void PrismizerAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    audioProcessor.noteOnVel = rawVolume.slider.getValue(); //not sure what this is even doing
    
    //handle smoothing updates
    if(slider == &smoothing.slider)
    {
        for (int i = 0; i < audioProcessor.synth.getNumVoices(); ++i){
            if (auto voice = dynamic_cast<PrismVoice*>(audioProcessor.synth.getVoice(i))){
                voice->setPitchSmoothDuration(audioProcessor.sr, *audioProcessor.params.getRawParameterValue("smoothing"));
            }
        }
    }
    
    //handle detune updates
    if(slider == &detune.slider)
    {
        for (int i = 0; i < audioProcessor.synth.getNumVoices(); ++i){
            if (auto voice = dynamic_cast<PrismVoice*>(audioProcessor.synth.getVoice(i))){
                voice->setDetuneRate(*audioProcessor.params.getRawParameterValue("detune"));
            }
        }
    }
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
    rawVolume.setTopLeftPosition(400, 0);
    ADSR.setTopLeftPosition(400, 200);
    smoothing.setTopLeftPosition(0, 0);
    detune.setTopLeftPosition(100, 0);
    spread.setTopLeftPosition(200, 0);
    vibrato.setTopLeftPosition(0, 200);
    tremolo.setTopLeftPosition(200, 200);
    wetVolume.setTopLeftPosition(rawVolume.getX() + rawVolume.getWidth(), 0);
    
}

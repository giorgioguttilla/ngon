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
    
    tKey.decodeNotesDown((unsigned int)*audioProcessor.params.getRawParameterValue("tunerKeyState"));
        
    //ValueTree pointer initializations
    
    autotuneValue = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.params, "autotune", autotuneToggle);
    
    
    
    fc1VolumeValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "follower1Volume", fc1.pitchSlider);
    
    fc2VolumeValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "follower2Volume", fc2.pitchSlider);
    
    fc1ActiveValue = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.params, "follower1Active", fc1.toggle);
    
    fc2ActiveValue = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.params, "follower2Active", fc2.toggle);
    
    
    
    attackValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "attack", ADSR.attack.slider);
    
    decayValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "decay", ADSR.sustain.slider);
    
    sustainValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "sustain", ADSR.sustain.slider);
    
    releaseValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "release", ADSR.release.slider);
    
    
    
    rawVolumeValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "rawVolume", rawVolume.slider);
    
    wetVolumeValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.params, "wetVolume", wetVolume.slider);
    
    
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
    
    //debug text box
    te.setText("test");
    te.setSize(400,50);
    
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
    
    addAndMakeVisible(&te);
    
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
    auto p = (juce::AudioParameterInt *)audioProcessor.params.getParameter("tunerKeyState");
    *p = tKey.encodeNotesDown();

//    DBG(*audioProcessor.params.getRawParameterValue("tunerKeyState"));
}

//sets tunkerkeyboard target value. unset if no autotune active or no note detected
void PrismizerAudioProcessorEditor::timerCallback()
{
    int noteMod = dynamic_cast<PrismizerAudioProcessor &>(processor).getTargetFreqAsNote() % 12;
    tKey.setTarget(autotuneToggle.getToggleState() ? noteMod : -1);
    
    te.setText(std::to_string(audioProcessor.yin->yinBuffer[0]) + " " +
               std::to_string(audioProcessor.yin->yinBuffer[1]) + " " +
               std::to_string(audioProcessor.yin->yinBuffer[2]) + " " +
               std::to_string(audioProcessor.yin->yinBuffer[3]) + " " +
               std::to_string(audioProcessor.yin->yinBuffer[4]) + " " +
               std::to_string(audioProcessor.yin->probability) + " " +
               std::to_string(audioProcessor.pitchEst));

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
    
    //debug text box
    te.setTopLeftPosition(5, 5);
}

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "VolumeSlider.h"

//==============================================================================
/**
*/
class PrismizerAudioProcessorEditor  :
    public juce::AudioProcessorEditor,
    private juce::Slider::Listener,
    public juce::Button::Listener
{
public:
    PrismizerAudioProcessorEditor (PrismizerAudioProcessor&);
    ~PrismizerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button *button) override;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PrismizerAudioProcessor& audioProcessor;
    
    //IN
    
    juce::ToggleButton autotuneToggle;
    
    //PROCESS
    
    
    
    //OUT
    
    VolumeSlider rawVolume;
    VolumeSlider wetVolume;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrismizerAudioProcessorEditor)
};

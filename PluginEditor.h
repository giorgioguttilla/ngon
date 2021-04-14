/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "VolumeSlider.h"
#include "FollowerControl.h"
#include "AdsrControls.h"
#include "TunerKeyboard.h"
#include "LFOGroup.h"

//==============================================================================
/**
*/
class PrismizerAudioProcessorEditor  :
    public juce::AudioProcessorEditor,
    private juce::Slider::Listener,
    public juce::Button::Listener,
    public juce::Timer
{
public:
    PrismizerAudioProcessorEditor (PrismizerAudioProcessor&);
    ~PrismizerAudioProcessorEditor() override;

    //==============================================================================
    void timerCallback() override;
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button *button) override;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PrismizerAudioProcessor& audioProcessor;

    //ADSR
    AdsrControls ADSR;
    
    //PITCH
    VolumeSlider smoothing;
    VolumeSlider detune;
    VolumeSlider spread;
    
    //MODULATION
    LFOGroup vibrato;
    LFOGroup tremolo;
    
private:
    //OUT
    
    VolumeSlider rawVolume;
    VolumeSlider wetVolume;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrismizerAudioProcessorEditor)
    
public:
    
    //attachments for updating params
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseValue;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> smoothingValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> detuneValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> spreadValue;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> vibratoRateValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> vibratoDepthValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> vibratoTriggerValue;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> tremoloRateValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> tremoloDepthValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> tremoloTriggerValue;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rawVolumeValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetVolumeValue;
};

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "./Yin/Yin.h"
#include "PitchYIN.h"
#include "WindowManager.h"

//==============================================================================
/**
*/
class PrismizerAudioProcessor  : public juce::AudioProcessor
{
public:
    float noteOnVel;
    
    //Pitch Shift/Detection Values==================================================
    
    float shift = 2;
    double sr = 0;
    double oversampling = 32;
    double fftsize = 1024;
    
    float pitchEst = 0;
    
//    PitchYIN* pitchYIN;
//    Yin *yin;
    WindowManager *wm;
    
    int getMidiNoteFromHz (float hz);
    
    //==============================================================================
    PrismizerAudioProcessor();
    ~PrismizerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrismizerAudioProcessor)
    
};

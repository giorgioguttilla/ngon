/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Yin.h"
#include "WindowManager.h"
#include "PrismSynth.h"
#include "PitchShift.h"

//==============================================================================
/**
*/
class PrismizerAudioProcessor  : public juce::AudioProcessor
{
public:
    float noteOnVel;
    
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
    
    //==============================================================================
    
    int getTargetFreqAsNote();
    
    juce::AudioProcessorValueTreeState params;

private:
    
    //Creates window for pitch detection
    WindowManager *wm;
    float winsize = 1024;
    
    //Synth class
    juce::Synthesiser synth;
    
    //processBuffer will hold edited signal from synth, used to separate raw and modded signal
    juce::AudioBuffer<float> processBuffer;
    
    //sample rate
    double sr = 0;
    
    //rolling pitch estimation
    float pitchEst = 0;
    
    //shifter for optional autotune sequence
    PitchShift autotuneShift;
    float tFreq = 8.1758;    //target frequency for autotune
    std::vector<int> notesTk = {0,1,2,3,4,5,6,7,8,9,10,11}; //allowed notes for autotune

    //rounds supplied freq to closest midi note as a frequency from provided vector. Vector takes the form of: 0 = c, 1 = c#...
    static float roundFreqToNearestNote(float inFreq, std::vector<int> useNotes);
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrismizerAudioProcessor)
};

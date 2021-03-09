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
    
    juce::AudioProcessorValueTreeState params;

private:
    
    //Creates window for pitch detection
    WindowManager *wm;
    float winsize = 1024;
    
    //Synth class
    juce::Synthesiser synth;
    
    //processBuffer will hold edited signal from synth, used to separate raw and modded signal
    juce::AudioBuffer<float> processBuffer;
    
    double sr = 0;
    float pitchEst = 0;
    
    //rounds supplied freq to closest midi note from provided vector. Vector takes the form of: 0 = c, 1 = c#...
    static float roundFreqToNearestNote(float inFreq, std::vector<int> useNotes);
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrismizerAudioProcessor)
};

/*
  ==============================================================================

    PrismVoice.h
    Created: 2 Mar 2021 10:31:47pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PrismSound.h"
#include "PitchShift.h"


class PrismVoice : public juce::SynthesiserVoice {
    
public:
    PrismVoice();
    ~PrismVoice();
    bool canPlaySound (juce::SynthesiserSound *sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels, juce::AudioBuffer<float> *pbp);
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    juce::AudioBuffer<float> *getWriteBuffer();
//    juce::AudioBuffer<float> getProcessBuffer();
    void setProcessBufferPtr(juce::AudioBuffer<float> *pbp);
    void setInPitch (float pitch);
    
private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    
    juce::AudioBuffer<float> tempBuf;
    juce::AudioBuffer<float> *processBufferPtr;
    
    PitchShift pShift;
    
    float inPitch;
    float outPitch = 440;
    
    long fftFrameSize = 1024;
    long os = 32;
};

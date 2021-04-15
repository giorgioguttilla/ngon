///*
//  ==============================================================================
//
//    PrismVoice.h
//    Created: 2 Mar 2021 10:31:47pm
//    Author:  Giorgio Guttilla
//
//  ==============================================================================
//*/
//
//#pragma once
//#include <JuceHeader.h>
//#include "PrismSound.h"
//#include "PitchShift.h"
//
//
//class PrismVoice : public juce::SynthesiserVoice {
//
//public:
//    PrismVoice();
//    ~PrismVoice();
//    bool canPlaySound (juce::SynthesiserSound *sound) override;
//    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
//    void stopNote (float velocity, bool allowTailOff) override;
//    void pitchWheelMoved (int newPitchWheelValue) override;
//    void controllerMoved (int controllerNumber, int newControllerValue) override;
//    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels, juce::AudioBuffer<float> *pbp);
//    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
//    juce::AudioBuffer<float> *getWriteBuffer();
//    void setProcessBufferPtr(juce::AudioBuffer<float> *pbp);
//    void setInPitch (float pitch);
//
//    juce::ADSR adsr;
//    juce::ADSR::Parameters adsrParams;
//
//private:
//
//    juce::AudioBuffer<float> tempBuf;
//    juce::AudioBuffer<float> *processBufferPtr;
//
//    std::unique_ptr<PitchShift> pShift;
//
//    float inPitch;
//    float outPitch = 440;
//
//    long fftFrameSize = 1024;
//    long os = 32;
//};



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
#include "FFTAccumulator.h"
#include "PitchProcessor.h"


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
    void setProcessBufferPtr(juce::AudioBuffer<float> *pbp);
    void setInPitch (float pitch);
    void setPitchSmoothDuration(double sr, float rate);
    void setDetuneRate(float rate);
    
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PrismVoice)
    
    juce::AudioBuffer<float> tempBuf;
    juce::AudioBuffer<float> *processBufferPtr;
    
    std::unique_ptr<PitchShift> pShift;
    
    float inPitch;
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Multiplicative> outPitch {440};
    
    float detuneLinearValue = 0.0;
    float detuneRate = 0.0;
    
    long fftFrameSize = 1024;
    long os = 32;
};

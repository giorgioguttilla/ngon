/*
  ==============================================================================

    PrismVoice.cpp
    Created: 2 Mar 2021 10:31:47pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#include "PrismVoice.h"
#include <iostream>
#include <math.h>
#include <tgmath.h>



PrismVoice::PrismVoice()
{
    
}

PrismVoice::~PrismVoice()
{
    
}

bool PrismVoice::canPlaySound (juce::SynthesiserSound *sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void PrismVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    adsr.noteOn();
    outPitch.setTargetValue(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    
    detuneLinearValue = log2(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    
}

void PrismVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
}

void PrismVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void PrismVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void PrismVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels, juce::AudioBuffer<float> *pbp)
{
    pShift = std::make_unique<PitchShift>(sampleRate, 1024);
    
    //default constructed, mostly redundant
    adsr.setSampleRate(sampleRate);
    adsr.setParameters(adsrParams);
    
    //only need 1 channel for tempbuf
    tempBuf.setSize(1, samplesPerBlock);
    tempBuf.clear();
    
    setProcessBufferPtr(pbp);
    
    outPitch.reset(sampleRate, 0.0);
    
}

void PrismVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    
    //detuneLinearValue is converted to exponential scale and difference is found between it and played note
    float detuneDifference = pow(2, detuneLinearValue) - outPitch.getTargetValue();
    
    //gets ratio between pitch of raw and pitch of played note with detune difference added/subtracted
    float adjOutPitch = outPitch.getNextValue() + detuneDifference;
    
    float shift = PitchShift::getshiftRatio(inPitch, adjOutPitch);
    
    
    //copies in buffer to temp, does processing, and adds back to out buffer
    tempBuf.clear();
    
    tempBuf.copyFrom(0, startSample, outputBuffer.getReadPointer(0), numSamples);

    pShift->smbPitchShift(shift, numSamples, 1024, 32, (float*)tempBuf.getReadPointer(0), tempBuf.getWritePointer(0));
    
    adsr.applyEnvelopeToBuffer(tempBuf, startSample, numSamples);
    
    //sends to each channel equally, might need to change later
    processBufferPtr->addFrom(0, startSample, tempBuf.getReadPointer(0), numSamples);
    processBufferPtr->addFrom(1, startSample, tempBuf.getReadPointer(0), numSamples);
    
    
    //bounds on detune, totally unnecessary to be this high/low but 2^14.288 = 20000 and 2^4.322 = 20
    if(detuneLinearValue > 14.288) detuneLinearValue = 14.288;
    if(detuneLinearValue < 4.322) detuneLinearValue = 4.322;
    
    //linear value is moved by a fixed interval, 300 is a sweet spot
    detuneLinearValue += detuneRate/300;
    
    DBG("+++++++++++++");
    DBG(pow(2, detuneLinearValue));
    DBG("+++++++++++++");
    
}



juce::AudioBuffer<float>* PrismVoice::getWriteBuffer()
{
    return &tempBuf;
}

void PrismVoice::setProcessBufferPtr(juce::AudioBuffer<float> *pbp){
    processBufferPtr = pbp;
}

void PrismVoice::setInPitch(float pitch)
{
    inPitch = pitch;
}

void PrismVoice::setPitchSmoothDuration(double sr, float rate)
{
    float tv = outPitch.getTargetValue();
    
    outPitch.reset(sr, rate/100);
    
    outPitch.setTargetValue(tv);
}

void PrismVoice::setDetuneRate(float rate)
{
    detuneRate = rate;
}

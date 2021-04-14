/*
  ==============================================================================

    PrismVoice.cpp
    Created: 2 Mar 2021 10:31:47pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#include "PrismVoice.h"
#include <iostream>

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
//    outPitch = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    outPitch.setTargetValue(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
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
        
    tempBuf.setSize(1, samplesPerBlock);
    tempBuf.clear();
    
    setProcessBufferPtr(pbp);
    
    outPitch.reset(sampleRate, 0.0);
    
}

void PrismVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    
    //gets ratio between pitch of raw and pitch of played note
    float shift = PitchShift::getshiftRatio(inPitch, outPitch.getNextValue());

    
    //copies in buffer to temp, does processing, and adds back to out buffer
    tempBuf.clear();
    
    tempBuf.copyFrom(0, startSample, outputBuffer.getReadPointer(0), numSamples);

    pShift->smbPitchShift(shift, numSamples, 1024, 32, (float*)tempBuf.getReadPointer(0), tempBuf.getWritePointer(0));
    
    adsr.applyEnvelopeToBuffer(tempBuf, startSample, numSamples);
    
    //sends to each channel equally, might need to change later
    processBufferPtr->addFrom(0, startSample, tempBuf.getReadPointer(0), numSamples);
    processBufferPtr->addFrom(1, startSample, tempBuf.getReadPointer(0), numSamples);
    
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

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

void PrismVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels, juce::AudioBuffer<float> *pbp, PrismizerAudioProcessor *p)
{
    processor = p;
    
    pShift = std::make_unique<PitchShift>(sampleRate, 1024);
    
    //default constructed, mostly redundant
    adsr.setSampleRate(sampleRate);
    adsr.setParameters(adsrParams);
    
    //only need 1 channel for tempbuf
    tempBuf.setSize(1, samplesPerBlock);
    tempBuf.clear();
    
    setProcessBufferPtr(pbp);
    
    outPitch.reset(sampleRate, 0.0);
    
    //TODO: fix filter initialization, this is placeholder
    filter = std::make_unique<juce::IIRFilter>();
    filter->setCoefficients(juce::IIRCoefficients::makeLowPass(sampleRate, outPitch.getCurrentValue(), 1.0));
    
}

void PrismVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    if(processor != nullptr)
    {
        
//        setPitchSmoothDuration(getSampleRate(), (float)*processor->params.getRawParameterValue("smoothing"));
//
//        setDetuneRate((float)*processor->params.getRawParameterValue("detune"));
//
//        setSpreadLevel((float)*processor->params.getRawParameterValue("spread"));
//
//        setFilterOffset((float)*processor->params.getRawParameterValue("filterOffset"));
//
//        setFilterWidth((float)*processor->params.getRawParameterValue("filterWidth"));
    }
    
    if(processor != nullptr)
    {
        
        setPitchSmoothDuration(getSampleRate(), (float)*processor->params.getRawParameterValue("smoothing"));
        
        float detuneRate = (float)*processor->params.getRawParameterValue("detune");
    
        float spreadLevel = (float)*processor->params.getRawParameterValue("spread");
    
        bool filterIsActive = (bool)*processor->params.getRawParameterValue("filterToggle");
        
        float filterOffset = (float)*processor->params.getRawParameterValue("filterOffset");
        
        float filterWidth = (float)*processor->params.getRawParameterValue("filterWidth");
        
        //TODO: for some reason getraw doesnt update when state is updated in plugineditor
        int filterType = (int)processor->params.state.getProperty("filterType");
//        int filterType = (int)*processor->params.getRawParameterValue("filterType");
        
        DBG(detuneRate);
        DBG(spreadLevel);
        DBG(std::to_string(filterIsActive));
        DBG(filterOffset);
        DBG(filterWidth);
        DBG(filterType);
        
        //detuneLinearValue is converted to exponential scale and difference is found between it and played note
        float detuneDifference = pow(2, detuneLinearValue) - outPitch.getTargetValue();
        
        //gets ratio between pitch of raw and pitch of played note with detune difference added/subtracted
        float adjOutPitch = outPitch.getNextValue() + detuneDifference;
        
        //ratio between in and out pitch
        float shift = PitchShift::getshiftRatio(inPitch, adjOutPitch);
        
        //pan will be applied as gain to L, inverse to R
        float panLevel = (spreadLevel * (log2(shift) / 2));
        
        
        //copies in buffer to temp, does processing, and adds back to out buffer
        tempBuf.clear();
        
        tempBuf.copyFrom(0, startSample, outputBuffer.getReadPointer(0), numSamples);

        pShift->smbPitchShift(shift, numSamples, 1024, 32, (float*)tempBuf.getReadPointer(0), tempBuf.getWritePointer(0));
        
        adsr.applyEnvelopeToBuffer(tempBuf, startSample, numSamples);
        
    //    for (int i = 0; i < 5; i++)
    //    {
    //        DBG(filter->getCoefficients().coefficients[i]);
    //    }
        
        //sends to each channel equally, might need to change later
        processBufferPtr->addFrom(0, startSample, tempBuf.getReadPointer(0), numSamples, 0.5 + panLevel);
        processBufferPtr->addFrom(1, startSample, tempBuf.getReadPointer(0), numSamples, 0.5 - panLevel);
        
        
        //bounds on detune, totally unnecessary to be this high/low but 2^14.288 = 20000 and 2^4.322 = 20
        if(detuneLinearValue > 14.288) detuneLinearValue = 14.288;
        if(detuneLinearValue < 4.322) detuneLinearValue = 4.322;
        
        //linear value is moved by a fixed interval, 300 is a sweet spot
        detuneLinearValue += detuneRate/300;
    }
   
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
    if(abs(smoothRate - rate) > 0.001)
    {
        float tv = outPitch.getTargetValue();
        
        outPitch.reset(sr, rate/100);
        
        outPitch.setTargetValue(tv);
        
        smoothRate = rate;
    }
    
}

//void PrismVoice::setDetuneRate(float rate)
//{
//    detuneRate = rate;
//}
//
//void PrismVoice::setSpreadLevel(float level)
//{
//    spreadLevel = level;
//}
//
//void PrismVoice::setIsFilterActive(bool isActive)
//{
//    filterIsActive = isActive;
//}
//void PrismVoice::setFilterOffset(float offset)
//{
//    filterOffset = offset;
//    updateFilter();
//}
//void PrismVoice::setFilterWidth(float width)
//{
//    filterWidth = width;
//    updateFilter();
//}
//void PrismVoice::setFilterType(int type)
//{
//    filterType = type;
//    updateFilter();
//}

void PrismVoice::updateFilter(float filterOffset, float filterWidth, int filterType)
{
    //TODO: filterOffset should work based on pitch
    float freq = pow(2, filterOffset * 14.3);
    float q = pow(2, (1.0 - filterWidth) * 3.0);          //1-8
    
    if(filterType == 0)
    {
        filter->setCoefficients(juce::IIRCoefficients::makeLowPass(getSampleRate(), freq, q));
    }
    if(filterType == 1)
    {
        filter->setCoefficients(juce::IIRCoefficients::makeBandPass(getSampleRate(), freq, q));
    }
    if(filterType == 2)
    {
        filter->setCoefficients(juce::IIRCoefficients::makeHighPass(getSampleRate(), freq, q));
    }
    
}

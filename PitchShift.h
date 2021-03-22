/*
  ==============================================================================

    PitchShift.h
    Created: 3 Mar 2021 4:04:11pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#pragma once

#define MAX_FRAME_LENGTH 8192

#include <juce_dsp/juce_dsp.h>

class PitchShift {
    
private:
    float gInFIFO[MAX_FRAME_LENGTH];
    float gOutFIFO[MAX_FRAME_LENGTH];
    float gFFTworksp[2*MAX_FRAME_LENGTH];
    float gLastPhase[MAX_FRAME_LENGTH/2+1];
    float gSumPhase[MAX_FRAME_LENGTH/2+1];
    float gOutputAccum[2*MAX_FRAME_LENGTH];
    float gAnaFreq[MAX_FRAME_LENGTH];
    float gAnaMagn[MAX_FRAME_LENGTH];
    float gSynFreq[MAX_FRAME_LENGTH];
    float gSynMagn[MAX_FRAME_LENGTH];
    long gRover = false;
    long gInit = false;
    
    std::unique_ptr<juce::dsp::FFT> fft;
    
    float sampleRate = 44100;
    
public:
    PitchShift();
    ~PitchShift();
    void setSampleRate(float sr);
    void smbFft(float *fftBuffer, long fftFrameSize, long sign);
    double smbAtan2(double x, double y);
    void smbPitchShift(float pitchShift, long numSampsToProcess, long fftFrameSize, long osamp, float *indata, float *outdata);
    
    static float getshiftRatio(float inFreq, float tFreq);
};

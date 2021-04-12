/*
  ==============================================================================

    PitchProcessor.h
    Created: 1 Apr 2021 9:06:55pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#pragma once

#define MAX_FRAME_LENGTH 8192

#include "FFTAccumulator.h"
#include <memory>

class PitchProcessor {
    
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
    float sampleRate = 44100;
    FFTAccumulator *accumulator;
    
public:
    PitchProcessor(float sr);
    ~PitchProcessor();
    void setSampleRate(float sr);
    void smbFft(float *fftBuffer, long fftFrameSize, long sign);
    double smbAtan2(double x, double y);
    void smbPitchShift(float pitchShift, long numSampsToProcess, long fftFrameSize, long osamp, float *indata, float *outdata);
    void setAccumulator(FFTAccumulator *acc);
};




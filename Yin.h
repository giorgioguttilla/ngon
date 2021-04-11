#ifndef Yin_h
#define Yin_h
//#include "WProgram.h"

#include <vector>

class Yin{
    
public:
    Yin();
public:
    Yin(float sampleRate,int bufferSize);
public:
    void initialize(float sampleRate,int bufferSize);
    
public:
    float getPitch(float* buffer);
public:
    float getProbability();
    
private:
    float parabolicInterpolation(int tauEstimate);
private:
    int absoluteThreshold();
private:
    void cumulativeMeanNormalizedDifference();
private:
    void difference(float* buffer);
private: public:
    double threshold;
    int bufferSize;
    int halfBufferSize;
    float sampleRate;
    std::vector<float> yinBuffer;
    float probability;
    
};

#endif



//#ifndef Yin_h
//#define Yin_h
////#include "WProgram.h"
//class Yin{
//
//public:
//	Yin();
//public:
//	Yin(float sampleRate,int bufferSize);
//public:
//	void initialize(float sampleRate,int bufferSize);
//
//public:
//	float getPitch(float* buffer);
//public:
//	float getProbability();
//
//private:
//	float parabolicInterpolation(int tauEstimate);
//private:
//	int absoluteThreshold();
//private:
//	void cumulativeMeanNormalizedDifference();
//private:
//	void difference(float* buffer);
//private:
//	double threshold;
//	int bufferSize;
//	int halfBufferSize;
//	float sampleRate;
//	float* yinBuffer;
//	float probability;
//};
//
//#endif

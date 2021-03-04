
#pragma once

#include <JuceHeader.h>

class PrismSynth : juce::Synthesiser {
private:
    
public:
    void renderNextBlockWithProcessBuffer(juce::AudioBuffer<float> &outputAudio, const juce::MidiBuffer &inputMidi, int startSample, int numSamples);
};

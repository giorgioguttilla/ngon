/*
  ==============================================================================

    PrismSynth.cpp
    Created: 3 Mar 2021 9:00:03pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#include "PrismSynth.h"


void PrismSynth::renderNextBlockWithProcessBuffer(juce::AudioBuffer<float> &outputAudio, const juce::MidiBuffer &inputMidi, int startSample, int numSamples)
{
    renderNextBlock(outputAudio, inputMidi, startSample, numSamples);
}

/*
  ==============================================================================

    PrismSound.h
    Created: 2 Mar 2021 10:32:10pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PrismSound : public juce::SynthesiserSound {
    
public:
    bool appliesToNote (int midiNoteNumber) override {return true;}
    bool appliesToChannel (int midiChannel) override {return true;}
};

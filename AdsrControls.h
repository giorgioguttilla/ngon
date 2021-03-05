/*
  ==============================================================================

    AdsrControls.h
    Created: 4 Mar 2021 9:18:12pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "VolumeSlider.h"

//==============================================================================
/*
*/
class AdsrControls  : public juce::Component
{
public:
    AdsrControls();
    ~AdsrControls() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    VolumeSlider attack;
    VolumeSlider decay;
    VolumeSlider sustain;
    VolumeSlider release;
    
    VolumeSlider *adsr[4] = {&attack, &decay, &sustain, &release};

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrControls)
};

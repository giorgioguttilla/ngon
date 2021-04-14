/*
  ==============================================================================

    LFOGroup.h
    Created: 13 Apr 2021 8:47:03am
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "VolumeSlider.h"

//==============================================================================
/*
*/
class LFOGroup  : public juce::Component
{
public:
    LFOGroup();
    ~LFOGroup() override;
    
    VolumeSlider rateSlider;
    VolumeSlider depthSlider;
    juce::ToggleButton triggerButton;
    juce::Label label;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void setText(std::string text);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOGroup)
};

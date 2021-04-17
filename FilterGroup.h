/*
  ==============================================================================

    FilterGroup.h
    Created: 17 Apr 2021 1:05:05pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FilterGraph.h"
#include "VolumeSlider.h"

//==============================================================================
/*
*/
class FilterGroup  : public juce::Component
{
public:
    FilterGroup();
    ~FilterGroup() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    FilterGraph filterGraph;
    VolumeSlider offset;
    VolumeSlider width;
    juce::ToggleButton toggleButton;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterGroup)
};

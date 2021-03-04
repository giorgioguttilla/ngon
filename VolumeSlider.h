/*
  ==============================================================================

    VolumeSlider.h
    Created: 4 Mar 2021 1:36:43pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class VolumeSlider : juce::Slider {
    
public:
    VolumeSlider();
    VolumeSlider(const std::string text);
    ~VolumeSlider();
    
    juce::Slider slider;
    juce::Label label;
private:
    void init(const std::string text);
};

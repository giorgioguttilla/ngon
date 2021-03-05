/*
  ==============================================================================

    VolumeSlider.h
    Created: 4 Mar 2021 1:36:43pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class VolumeSlider : public juce::Component {
    
public:
    VolumeSlider();
    ~VolumeSlider();
    
    juce::Slider slider;
    juce::Label label;
    
    void setText(const std::string text);
    
    void resized() override;
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolumeSlider)
};

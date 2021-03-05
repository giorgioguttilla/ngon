/*
  ==============================================================================

    FollowerControl.h
    Created: 4 Mar 2021 6:58:10pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class FollowerControl : public juce::Component {
    
public:
    FollowerControl();
    ~FollowerControl();
    
    juce::Slider pitchSlider;
    juce::Label pitchLabel;
    
    juce::Label label;
    
    juce::ToggleButton toggle;
    
    void resized() override;
    void setText(const std::string text);
private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FollowerControl);
};


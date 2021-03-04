/*
  ==============================================================================

    VolumeSlider.cpp
    Created: 4 Mar 2021 1:36:43pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#include "VolumeSlider.h"

VolumeSlider::VolumeSlider(){
    init("Volume");
}

VolumeSlider::VolumeSlider(const std::string text){
    init(text);
}

VolumeSlider::~VolumeSlider(){
    
}

void VolumeSlider::init(const std::string text)
{
//    slider.setSliderStyle(juce::Slider::LinearVertical);
    slider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 200, 30);
    slider.setTextBoxIsEditable(true);

    slider.setNormalisableRange(juce::NormalisableRange<double>(0.0, 1.0));
    slider.setValue(1.0);

    slider.textFromValueFunction = [](double value)
    {
        return juce::String(value, 2);
    };
    
    
    
    label.setText(text, juce::dontSendNotification);
    label.attachToComponent(&slider, false);
    label.setColour(juce::Label::textColourId, juce::Colours::skyblue);
    label.setJustificationType (juce::Justification::centred);
}

/*
  ==============================================================================

    VolumeSlider.cpp
    Created: 4 Mar 2021 1:36:43pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#include "VolumeSlider.h"

VolumeSlider::VolumeSlider(){
    
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    
    setSize(100, 160);

    slider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    slider.setTextBoxIsEditable(true);

    slider.setNormalisableRange(juce::NormalisableRange<double>(0.0, 1.0));
    slider.setValue(1.0);

    slider.textFromValueFunction = [](double value)
    {
        return juce::String(value, 2);
    };
    
    slider.updateText();
    
    label.setText("Volume", juce::dontSendNotification);
    label.attachToComponent(&slider, false);
    label.setColour(juce::Label::textColourId, juce::Colours::skyblue);
    label.setJustificationType (juce::Justification::centred);
    
    
    
}

VolumeSlider::~VolumeSlider(){
    
}

void VolumeSlider::resized()
{
    label.setBounds(0, 0, getWidth(), 30);
    slider.setBounds(0, 30, getWidth(), getHeight() - 30);
}

void VolumeSlider::setText(const std::string text)
{
    label.setText(text, juce::dontSendNotification);
}



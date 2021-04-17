/*
  ==============================================================================

    FilterGroup.cpp
    Created: 17 Apr 2021 1:05:05pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterGroup.h"

//==============================================================================
FilterGroup::FilterGroup()
{
    
    offset.setText("offset");
    offset.slider.setSliderStyle(juce::Slider::LinearHorizontal);
    
    width.setText("width");
    width.slider.setSliderStyle(juce::Slider::LinearHorizontal);
    
    addAndMakeVisible(filterGraph);
    addAndMakeVisible(offset);
    addAndMakeVisible(width);
    addAndMakeVisible(toggleButton);
    
    setSize(200, 200);
    
}

FilterGroup::~FilterGroup()
{
}

void FilterGroup::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("FilterGroup", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void FilterGroup::resized()
{
    filterGraph.setBounds(0, 0, getWidth(), getHeight()/2);
    toggleButton.setBounds(0, getHeight()/2, getHeight()/4, getHeight()/4);
    offset.setBounds(getWidth()/4, getHeight()/2, getWidth()*0.75, getHeight()/4);
    width.setBounds(getWidth()/4, getHeight()*0.75, getWidth()*0.75, getHeight()/4);
}

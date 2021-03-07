/*
  ==============================================================================

    TaggedKey.h
    Created: 5 Mar 2021 3:01:45pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class TaggedKey  : public juce::ToggleButton
{
public:
    TaggedKey(int _note) : juce::ToggleButton()
    {
        note = _note;
    }

    ~TaggedKey() override
    {
    }
    
    void setNote(int _note)
    {
        note = _note;
    }
    
    int getNote()
    {
        return note;
    }

    void paint (juce::Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */
        // clear the background

        g.setColour (juce::Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }
    
protected:
    int note;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TaggedKey)
};

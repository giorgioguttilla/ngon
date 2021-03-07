/*
  ==============================================================================

    StickyKeyboard.h
    Created: 5 Mar 2021 11:09:38am
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class StickyKeyboard  : public juce::MidiKeyboardComponent
{
public:
    
    juce::MidiKeyboardState *state;
    
    StickyKeyboard(juce::MidiKeyboardState& s, Orientation o) : juce::MidiKeyboardComponent(s, o)
    {
        state = &s;
    }
    
    void mouseDown(const juce::MouseEvent &) override
    {
        return;
    }
    
    bool mouseDownOnKey(int midiNoteNumber, const juce::MouseEvent &e) override
    {
        for (int i = 0; i < 11; i++) {
            if(state->isNoteOn(getMidiChannel(), i)){
                DBG(i);
            }
        }
        
        return true;
    }
    
    void mouseUp(const juce::MouseEvent &e) override
    {
        for (int i = 0; i < 11; i++) {
            if(state->isNoteOn(getMidiChannel(), i)){
                DBG(i);
            }
        }
        return;
    }
    
    void mouseUpOnKey(int midiNoteNumber, const juce::MouseEvent &e) override
    {
        return;
    }

//    ~StickyKeyboard() override
//    {
//    }

//    void paint (juce::Graphics& g) override
//    {
//        /* This demo code just fills the component's background and
//           draws some placeholder text to get you started.
//
//           You should replace everything in this method with your own
//           drawing code..
//        */
//
//        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
//
//        g.setColour (juce::Colours::grey);
//        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
//
//        g.setColour (juce::Colours::white);
//        g.setFont (14.0f);
//        g.drawText ("StickyKeyboard", getLocalBounds(),
//                    juce::Justification::centred, true);   // draw some placeholder text
//    }

//    void resized() override
//    {
//        // This method is where you should set the bounds of any child
//        // components that your component contains..
//
//    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StickyKeyboard)
};

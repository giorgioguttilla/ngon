/*
  ==============================================================================

    FilterGraph.cpp
    Created: 16 Apr 2021 4:19:06pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterGraph.h"

//==============================================================================
FilterGraph::FilterGraph()
{
   
    setSize(200, 100);
    
//    addMouseListener(this, false);
    
}

FilterGraph::~FilterGraph()
{
}

void FilterGraph::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.fillAll();

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("FilterGraph", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
    
    float top = 0.7;
    float bottom = 0.3;
    float cZoneW = 0.15;
    float aZoneL = 0.5-cZoneW;
    float aZoneR = 0.5+cZoneW;
    
    hpPath.startNewSubPath(0, getHeight()*top);
    hpPath.lineTo(getWidth()*aZoneL, getHeight()*top);
    hpPath.quadraticTo(getWidth()/2, getHeight()*top, getWidth()/2, getHeight()/2);
    hpPath.quadraticTo(getWidth()/2, getHeight()*bottom, getWidth()*aZoneR, getHeight()*bottom);
    hpPath.lineTo(getWidth(), getHeight()*bottom);
    
    g.setColour (juce::Colours::blue);
    g.setOpacity(filterType == 2 ? 1 : 0.1);
    g.strokePath (hpPath, juce::PathStrokeType(5.0));
    
    
    
    lpPath.startNewSubPath(0, getHeight()*bottom);
    lpPath.lineTo(getWidth()*aZoneL, getHeight()*bottom);
    lpPath.quadraticTo(getWidth()/2, getHeight()*bottom, getWidth()/2, getHeight()/2);
    lpPath.quadraticTo(getWidth()/2, getHeight()*top, getWidth()*aZoneR, getHeight()*top);
    lpPath.lineTo(getWidth(), getHeight()*top);
    
    g.setColour (juce::Colours::red);
    g.setOpacity(filterType == 0 ? 1 : 0.1);
    g.strokePath (lpPath, juce::PathStrokeType(5.0));
    
    
    
    bpPath.startNewSubPath(0, getHeight()*top);
    bpPath.lineTo(getWidth()*aZoneL, getHeight()*top);
    bpPath.quadraticTo(getWidth()*(aZoneL+(cZoneW/2)), getHeight()*top, getWidth()*(aZoneL+(cZoneW/2)), getHeight()/2);
    bpPath.quadraticTo(getWidth()*(aZoneL+(cZoneW/2)), getHeight()*bottom, getWidth()/2, getHeight()*bottom);
    bpPath.quadraticTo(getWidth()*(aZoneR-(cZoneW/2)), getHeight()*bottom, getWidth()*(aZoneR-(cZoneW/2)), getHeight()/2);
    bpPath.quadraticTo(getWidth()*(aZoneR-(cZoneW/2)), getHeight()*top, getWidth()*aZoneR, getHeight()*top);
    bpPath.lineTo(getWidth(), getHeight()*top);
    
    g.setColour (juce::Colours::lightgreen);
    g.setOpacity(filterType == 1 ? 1 : 0.1);
    g.strokePath (bpPath, juce::PathStrokeType(5.0));
    
}

void FilterGraph::resized()
{
    
    

}

//void FilterGraph::mouseDown(const juce::MouseEvent &event)
//{
////    filterType += 1;
////    if(filterType > 2) filterType = 0;
////    DBG("ASDF");
//    
//    
//}


void FilterGraph::setFilterType(int type)
{
    filterType = type;
}

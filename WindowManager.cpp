//
//  WindowManager.cpp
//  Prismizer
//
//  Created by Giorgio Guttilla on 3/2/21.
//  Copyright © 2021 gguttilla. All rights reserved.
//
//  This class is simply meant to accumulate buffers of smaller sizes


#include <stdio.h>
#include <JuceHeader.h>
#include "WindowManager.h"



//creates new window array of wSize
WindowManager::WindowManager(int wSize, int bSize){
    
    bufferSize = bSize;
    
    if (bSize > wSize){
        windowSize = bSize;
    } else windowSize = wSize;
        
    maxStep = (wSize/bSize);
    window.clear();
}

WindowManager::~WindowManager(){

}

bool WindowManager::append(float* inData){
    
    if (isFull()){
        window.clear();
        curStep = 0;
    }

    for (int i = 0; i < bufferSize; i++) {
        window.push_back(inData[i]);
    }

    curStep++;
    
    return isFull();
}

bool WindowManager::isFull(){
    if(curStep == maxStep){
        return true;
    }
    return false;
}

std::vector<float> WindowManager::getWindow(){
    return window;
}

int WindowManager::getWindowSize(){
    return windowSize;
}

int WindowManager::getBufferSize(){
    return bufferSize;
}

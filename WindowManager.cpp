//
//  WindowManager.cpp
//  Prismizer
//
//  Created by Giorgio Guttilla on 3/2/21.
//  Copyright © 2021 gguttilla. All rights reserved.
//

#include <stdio.h>
#include <JuceHeader.h>
#include "WindowManager.h"



//creates new window array of wSize
WindowManager::WindowManager(int wSize, int bSize){
    
    bufferSize = bSize;
    
    if (bSize > wSize){
        windowSize = bSize;
    } else windowSize = wSize;
    
    window = (float*)malloc(windowSize * sizeof(float));
    
    maxStep = (wSize/bSize);
    clearWindow();
}

WindowManager::~WindowManager(){
    delete window;
}

void WindowManager::test(){
    DBG(bufferSize);
}

bool WindowManager::append(float* inData){
    
    if (isFull()){
        clearWindow();
    }
    
    int inc = curStep * bufferSize;
    
    for (int i = 0; i < bufferSize; i++) {
        window[inc + i] = inData[i];
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

float* WindowManager::getWindow(){
    return window;
}

int WindowManager::getWindowSize(){
    return windowSize;
}

void WindowManager::clearWindow(){
    
    for (int i = 0; i < windowSize; i++) {
        window[i] = 0;
    }
    curStep = 0;
}

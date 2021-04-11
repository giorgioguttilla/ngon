//
//  WindowManager.h
//  Prismizer
//
//  Created by Giorgio Guttilla on 3/2/21.
//  Copyright © 2021 gguttilla. All rights reserved.
//

//#ifndef WindowManager_h
//#define WindowManager_h
//
//class WindowManager
//{
//public:
//    WindowManager(int wSize, int bSize);
//    ~WindowManager();
//
//    void test();
//    bool append(float* inData);
//    float* getWindow();
//    int getWindowSize();
//    void clearWindow();
//    bool isFull();
//private:
//    int windowSize;
//    int bufferSize;
//    float* window;
//    int curStep;
//    int maxStep;
//};


#ifndef WindowManager_h
#define WindowManager_h

class WindowManager
{
public:
    WindowManager(int wSize, int bSize);
    ~WindowManager();
    
    bool append(float *inData);
    std::vector<float> getWindow();
    int getWindowSize();
    int getBufferSize();
    bool isFull();
private:
    int windowSize;
    int bufferSize;
    std::vector<float> window;
    int curStep = 0;
    int maxStep;
};

#endif

#pragma once

#include "ofMain.h"
#include "ofxLitSphere.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void mousePressed(int x, int y, int button);
    
    ofxLitSphere litSphere;
};

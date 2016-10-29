#pragma once
#include "ofMain.h"

class DisplacementSphereMesh {
	
public:
    
    ofParameterGroup *settings;
    ofParameter<float> details;
    ofParameter<float> displace;
    ofParameter<float> speed;

    // From GUI
    float positionX;
    float positionY;
    
    //OSC
    bool isPlaying;
    float touch_power;
    
    // Mesh
    ofLight light;
	ofEasyCam cam;
	ofVboMesh mainMesh;
    
    float *depths;
    float *speeds;
    float *forces;
    
    ofSpherePrimitive sphere;
    
    void setup();
    void update();
    void draw(bool triagles = false,  bool type = false);
    void setNormals(ofMesh &mesh);
};

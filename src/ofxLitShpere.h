#pragma once

#include "ofMain.h"

class ofxLitSphere {
    
public:
    
    ofShader    shader;
    
    ofImage texture;
    ofDirectory dir;
    int current;
    
    //--------------------------------------------------------------
    void setup(){
        ofEnableNormalizedTexCoords();
        ofDisableNormalizedTexCoords();
        ofEnableAlphaBlending();

		current = 0;
            
        shader.load("shaders/litsphere/vert.glsl", "shaders/litsphere/frag.glsl");
        loadNext();
        loadPrevious();
    }
    
    void loadAt(int number) {
        string directory = "MatCapZBrush/Lib/";
        dir.listDir(directory);

        current = number;
        if (dir.size() <= current) current = 0;
        
        string fileName = dir.getPath(current);
        ofLogVerbose("ofxLitSphere", "fileName " + fileName);
        texture.loadImage(fileName);
    }
    
    void loadNext() {
        string directory = "MatCapZBrush/Lib/";
        dir.listDir(directory);
        
        current++;
        if (dir.size() <= current) current = 0;
        
        string fileName = dir.getPath(current);
        ofLogVerbose("ofxLitSphere", "fileName " + fileName);
        texture.loadImage(fileName);
    }
    
    void loadPrevious() {
        string directory = "MatCapZBrush/Lib/";
        dir.listDir(directory);
        
        current--;
        if (current < 0) current = dir.size() - 1;
        
        string fileName = dir.getPath(current);
        ofLogVerbose("ofxLitSphere", "fileName " + fileName);
        texture.loadImage(fileName);

    }
    
    //--------------------------------------------------------------
    void update(){}
    
    void begin() {
        ofEnableNormalizedTexCoords();
        ofEnableTextureEdgeHack();
        
        shader.begin();
        shader.setUniformTexture("litsphereTexture", texture, 1);
    }
    
    void end() {
        shader.end();
    }
    
    void reload() {
        shader.load("shaders/litsphere/vert.glsl", "shaders/litsphere/frag.glsl");
    }
};

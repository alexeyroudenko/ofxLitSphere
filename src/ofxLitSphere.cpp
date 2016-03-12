
#include "ofxLitSphere.h"

//--------------------------------------------------------------
void ofxLitSphere::setup(){
    ofEnableNormalizedTexCoords();
    ofDisableNormalizedTexCoords();
    ofEnableAlphaBlending();
    
    current = 0;
    
    shader.load("shaders/litsphere/vert.glsl", "shaders/litsphere/frag.glsl");
    loadNext();
    loadPrevious();
}

void ofxLitSphere::loadAt(int number) {
    string directory = "MatCapZBrush/Lib/";
    dir.listDir(directory);
    
    current = number;
    if (dir.size() <= current) current = 0;
    
    string fileName = dir.getPath(current);
    ofLogVerbose("ofxLitSphere", "fileName " + fileName);
    texture.load(fileName);
}

void ofxLitSphere::loadNext() {
    string directory = "MatCapZBrush/Lib/";
    dir.listDir(directory);
    
    current++;
    if (dir.size() <= current) current = 0;
    
    string fileName = dir.getPath(current);
    ofLogVerbose("ofxLitSphere", "fileName " + fileName);
    texture.load(fileName);
}

void ofxLitSphere::loadPrevious() {
    string directory = "MatCapZBrush/Lib/";
    dir.listDir(directory);
    
    current--;
    if (current < 0) current = dir.size() - 1;
    
    string fileName = dir.getPath(current);
    ofLogVerbose("ofxLitSphere", "fileName " + fileName);
    texture.load(fileName);
    
}

int ofxLitSphere::getCurrent() {
    return current;
}

//--------------------------------------------------------------
void ofxLitSphere::update(){}

void ofxLitSphere::begin() {
    ofEnableNormalizedTexCoords();
    ofEnableTextureEdgeHack();
    shader.begin();
    shader.setUniformTexture("litsphereTexture", texture, 1);
}

void ofxLitSphere::end() {
    shader.end();
    ofDisableNormalizedTexCoords();
    ofDisableTextureEdgeHack();
}

void ofxLitSphere::reload() {
    shader.load("shaders/litsphere/vert.glsl", "shaders/litsphere/frag.glsl");
}
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetDataPathRoot("../../../../../data/");
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofDisableArbTex();
    ofEnableDepthTest();
    ofSetVerticalSync(true);
    
    litSphere.setup();
    litSphere.loadAt(2);

    litSphere02.setup();
    litSphere02.loadAt(24);
    
    ofSetConeResolution(40, 40, 40);
    
    displacement.setup();
    
    light.setAmbientColor(ofColor(200));
    light.setDiffuseColor(ofColor(200));
    light.setSpecularColor(ofColor(200));
    ofSetSmoothLighting(true);
    
    material.setAmbientColor(ofColor(150));
    material.setDiffuseColor(ofColor(150));
    material.setSpecularColor(ofColor(150));
    material.setEmissiveColor(ofFloatColor(10.0));
    material.setShininess(0.8);
}

//--------------------------------------------------------------
void ofApp::update(){
    displacement.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255);
    
    ofClear(0);
    ofPushMatrix();
    ofScale(2, 2);
    ofBackgroundGradient(ofColor(180), ofColor(70), OF_GRADIENT_CIRCULAR);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

    ofEnableAlphaBlending();
    ofEnableDepthTest();
    ofDisableNormalizedTexCoords();
    
    light.enable();

    // first
    litSphere.begin();
        displacement.draw();
    litSphere.end();

    // second
    litSphere02.begin();
        glPushMatrix();
        ofDrawSphere(0, 0, 150);
        ofPopMatrix();
    litSphere02.end();
//
//    light.disable();
    
    ofDisableDepthTest();
    ofEnableAlphaBlending();
    ofPopMatrix();
    ofDrawBitmapString(". , change sourse", ofPoint(20, 20));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'f') ofToggleFullscreen();
    if (key == '.') litSphere.loadNext();
    if (key == ',') litSphere.loadPrevious();
    if (key == ' ') ofLogVerbose(ofToString(litSphere.getCurrent()) + " " + ofToString(litSphere02.getCurrent()) + " " + ofToString(ofGetMouseY()));
        
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){}

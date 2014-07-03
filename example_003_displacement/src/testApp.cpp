#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofDisableArbTex();
    ofEnableDepthTest();
    ofSetVerticalSync(true);
    litSphere.setup();
    litSphere.loadAt(2);

    litSphere02.setup();
    litSphere02.loadAt(17);
    
    ofSetConeResolution(40, 40, 40);
    
    displacement.setup();
}

//--------------------------------------------------------------
void testApp::update(){
    //displacement.update(.02, .01, .22, ofGetFrameNum());
    displacement.update(.02, .01, .42, ofGetFrameNum());
}

#define COUNT 20
#define COUNT_FRAMES 90

//--------------------------------------------------------------
void testApp::draw(){
    
    ofClear(0, 0, 0, 255);
    
    ofBackgroundGradient(ofColor(180), ofColor(70), OF_GRADIENT_CIRCULAR);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    // hack
    material.begin();
    material.end();
    
    
    // first
    litSphere.begin();
        displacement.draw();
    litSphere.end();

    // second
    litSphere02.begin();
        glPushMatrix();
        ofDrawSphere(0, 0, 180);
        ofPopMatrix();
    litSphere02.end();

    ofPopMatrix();
    ofDrawBitmapStringHighlight("click to change sourse", ofPoint(20, 20));
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key == 'f') ofToggleFullscreen();
    if (key == '.') litSphere.loadNext();
    if (key == ',') litSphere02.loadNext();
    if (key == ' ') ofLogVerbose(ofToString(litSphere.current) + " " + ofToString(litSphere02.current) + " " + ofToString(ofGetMouseY()));
        
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    litSphere.loadNext();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

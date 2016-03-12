#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofDisableArbTex();
    ofEnableDepthTest();
    ofSetVerticalSync(true);
    litSphere.setup();
    ofSetConeResolution(40, 40, 40);
}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    litSphere.begin();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotate(ofGetFrameNum(), 0, -1, -1);
    ofDrawCone(100, 140);
    ofDrawSphere(200, 0, 70);
    ofDrawBox(-200, 0, 0, 80);
    litSphere.end();
    
    ofDrawBitmapStringHighlight("click to change sourse", ofPoint(0, 0));
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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

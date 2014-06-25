#include "testApp.h"

float               boxSize = 30;

//--------------------------------------------------------------
void testApp::setup(){
    ofDisableArbTex();
    ofEnableDepthTest();
    ofSetVerticalSync(true);
    litSphere.setup();
    litSphere.loadAt(18);

    litSphere02.setup();
    litSphere02.loadAt(7);
    
    ofSetConeResolution(40, 40, 40);
}

//--------------------------------------------------------------
void testApp::update(){
    
}

#define COUNT 20
#define COUNT_FRAMES 90

//--------------------------------------------------------------
void testApp::draw(){
    
    ofClear(0, 0, 0, 255);
    

    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    litSphere02.begin();
        ofPushMatrix();
        ofRotate(ofGetFrameNum() * 4.0, 1, -1, 0);
        for (int i = 0;  i < 4; i++) {
            ofRotate(90, 0, 0, 1);
            ofPushMatrix();
            ofTranslate(0, 55);
            ofDrawCone(100, 100);
            ofPopMatrix();
        }
        ofPopMatrix();
    litSphere02.end();

    litSphere.begin();
        float size = 60;
        glTranslatef(-size * COUNT / 2, -size * COUNT / 2, -300);
        for (int i=0; i < COUNT; i++)
        {
            for (int j=0; j < COUNT; j++)
            {
                glPushMatrix();
                glTranslatef(i * size, j * size, 0);
                glRotatef((ofGetFrameNum() / 2.0 + i - j) * 8.0, sin(i), 0, cos(i) );
                ofBox(0, 0, 0 * sin(i), boxSize);
                glPopMatrix();
            }
        }
        ofPopMatrix();
    litSphere.end();
    
    ofDrawBitmapStringHighlight("click to change sourse", ofPoint(0, 0));
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key == 'f') ofToggleFullscreen();
    if (key == '[') boxSize -= 10;
    if (key == ']') boxSize += 10;
    if (key == '.') litSphere.loadNext();
    if (key == ',') litSphere02.loadNext();
        
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

#include "DisplacementSphereMesh.h"

void DisplacementSphereMesh::setup() {
    
    settings = new ofParameterGroup();
    settings->setName("displacement");
    settings->add(details.set("details", 0.06, 0 ,1));
    settings->add(displace.set("displace", 0.8, 0, 1));
    settings->add(speed.set("speed", 0.1, 0 ,1));
    
    sphere.setRadius(150);
    sphere.setResolution(96);
    mainMesh = sphere.getMesh();
    depths = new float[sphere.getMesh().getNumVertices()];
    speeds = new float[sphere.getMesh().getNumVertices()];
    forces = new float[sphere.getMesh().getNumVertices()];
    for (int i = 0; i < sphere.getMesh().getNumVertices(); i++) {
        depths[i] = sphere.getMesh().getVertices()[i].length();
        speeds[i] = 0;
        forces[i] = 0;
    }
}

void DisplacementSphereMesh::update()  {
    mainMesh = sphere.getMesh();
    float time = speed * ofGetElapsedTimef();
    for (int i = 0; i < mainMesh.getNumVertices(); i++) {
        ofVec3f v = mainMesh.getVertex(i);
        float d = ofNoise(v.x * details * 0.1, v.y * details * 0.1, time) * displace * 100.0;
        //displace += 10.0 * ofNoise(v.x * 0.01, v.y * 0.01, time * .3);
        v = v + mainMesh.getNormal(i) * d;
        mainMesh.setVertex(i, v);
    }
    setNormals(mainMesh);
}

void DisplacementSphereMesh::draw(bool triagles,  bool type) {
    ofSetHexColor(0xffffff);
    ofPushMatrix();
    ofRotate(180, 0, 1, 0);
    if (type == true) ofRotate(180, 0, 1, 0);
    if (!triagles)
        mainMesh.drawFaces();
    
    ofSetHexColor(0x333333);
    ofSetLineWidth(1.0);
    ofEnableSmoothing();
    if (triagles)
        mainMesh.drawWireframe();
    ofSetHexColor(0xffffff);
    ofPopMatrix();
}

void DisplacementSphereMesh::setNormals( ofMesh &mesh ){
    int nV = mesh.getNumVertices();
    int nT = mesh.getNumIndices() / 3;
    vector<ofPoint> norm( nV ); //Array for the normals
    for (int t=0; t<nT; t++) {
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        ofPoint dir = - ((v2 - v1).getCrossed( v3 - v1 )).getNormalized();
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    mesh.clearNormals();
    
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
        mesh.addNormal(norm[i]);
    }
}

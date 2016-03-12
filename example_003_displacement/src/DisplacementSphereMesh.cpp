#include "DisplacementSphereMesh.h"

void DisplacementSphereMesh::setup() {
    sphere.setRadius(150);
    sphere.setResolution(96);
    //sphere.setResolution(48);
    mainMesh = sphere.getMesh();
    //mainMesh.enableColors();
    depths = new float[sphere.getMesh().getNumVertices()];
    speeds = new float[sphere.getMesh().getNumVertices()];
    forces = new float[sphere.getMesh().getNumVertices()];
    for (int i = 0; i < sphere.getMesh().getNumVertices(); i++) {
        depths[i] = sphere.getMesh().getVertices()[i].length();
        speeds[i] = 0;
        forces[i] = 0;
    }
}

void DisplacementSphereMesh::update() {
    update(0.5, 0.5, 0.01);
}

void DisplacementSphereMesh::update(float mouseX, float mouseY, float volume, int curentFrame)  {
    mainMesh = sphere.getMesh();
    float time = .02 * ofGetFrameNum();
    if (curentFrame != -1) time = 0.02 * curentFrame;
    float index = 1.0 * (ofGetFrameNum()) / 20;
    for (int i = 0; i < mainMesh.getNumVertices(); i++) {
        ofVec3f v = mainMesh.getVertex(i);
        float displace = ofNoise(v.x * 1.1 * mouseX * (0.02 + volume), v.y * 2.1 *  mouseX * (0.02 + volume), time * 1.2 + 30 + 2. * volume);
        displace += 10.0 * ofNoise(v.x * 0.01, v.y * 0.01, time * .3) * 1.0 * volume;
        v = v + mainMesh.getNormal(i) * displace * (0.01 + volume * volume) * 10000. * mouseY;
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

//Universal function which sets normals for the triangle mesh
void DisplacementSphereMesh::setNormals( ofMesh &mesh ){
    
    //The number of the vertices
    int nV = mesh.getNumVertices();
    
    //The number of the triangles
    int nT = mesh.getNumIndices() / 3;
    
    vector<ofPoint> norm( nV ); //Array for the normals
    
    //Scan all the triangles. For each triangle add its
    //normal to norm's vectors of triangle's vertices
    for (int t=0; t<nT; t++) {
        
        //Get indices of the triangle t
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        
        //Get vertices of the triangle
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        
        //Compute the triangle's normal
        ofPoint dir = - ((v2 - v1).getCrossed( v3 - v1 )).getNormalized();
        
        
        //Accumulate it to norm array for i1, i2, i3
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    
    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
}
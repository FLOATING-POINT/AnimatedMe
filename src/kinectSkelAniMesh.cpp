#include "kinectSkelAniMesh.h"


//--------------------------------------------------------------
void kinectSkelAniMesh::setup(){

    pntMode = 1;

    drawMeshWireframes  = true;
    doDraw              = true;


    img.loadImage("frame.png");
    imgMesh.loadImage("0776250001338289736.png");
    //imgMesh.loadImage("0225121001338555975.png");
    //imgMesh.loadImage("43-00384893.png");

    ofBackground(50,50,50);

    offsetX         = 26;
    offsetY         = 100;

    meshOffsetX     = 1000;
    meshOffsetY     = 100;

    skelOriginX     = 0;
    skelOriginY     = 0;

    skelDiffX       = 0;
    skelDiffY       = 0;

    meshW           = 400.0f;
    meshH           = 606.0f;
    nPntsSkel       = 24; // 20 skel pnts + 4 corner points

    nPntsPerSkelPnt = 0;
    skelPntRadius   = 20; //radius in pixels around each skel point

    meshRadialPnts.resize(nPntsSkel);
    for(int i =4; i < nPntsSkel; i++){
        meshRadialPnts[i].reserve(nPntsPerSkelPnt);
    }

    meshVertexPntsForSkelPnts.resize(nPntsSkel);

    resetPoints();

    // read the stored points
    readMeshPoints();
    createRadialPnts();
    createTriangles();
    createMesh();

    // OF_PRIMITIVE_TRIANGLES means every three vertices create a triangle
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);


}

//--------------------------------------------------------------
void kinectSkelAniMesh::update(){



}

//--------------------------------------------------------------
void kinectSkelAniMesh::draw(){


    if(doDraw){

    /*
    //---------------------------------------------------------------------

    ofPushMatrix();
    ofTranslate(offsetX, offsetY, 0);

        ofEnableAlphaBlending();
            ofSetColor(255,255,255);
            img.draw(0,0);
        ofDisableAlphaBlending();


        //-----------------------------------------------------
        // corner points

        for(int i =0; i < 4; i++){

            ofNoFill();
            ofSetLineWidth(0.25f);
            ofSetColor(0,0,255);
            ofRect(meshSkelPnts[i].x -3,meshSkelPnts[i].y-3, 6, 6 );

            ofSetColor(255,0,0);

            if(i>0){
                ofLine(meshSkelPnts[i-1].x,meshSkelPnts[i-1].y,meshSkelPnts[i].x,meshSkelPnts[i].y);
            } else {
                ofLine(meshSkelPnts[i].x,meshSkelPnts[i].y,meshSkelPnts[3].x,meshSkelPnts[3].y);
            }

        }
        //printf("--------------------------------------------------- \n");

        ofSetLineWidth(1.0f);

        //----------------------------------------------------------
        // skel points

        for(int i = 4; i < meshSkelPnts.size(); i++){

            ofFill();
            ofSetColor(255,0,0);
            ofCircle(meshSkelPnts[i].x ,meshSkelPnts[i].y,6);

            ofSetColor(250,250,250);
            ofDrawBitmapString(ofToString(i-4),meshSkelPnts[i].x +6 ,meshSkelPnts[i].y+4);

        }

        //---------------------------------------------------
        // radial points

        for(int i =4; i < nPntsSkel; i++){

            for(int j =0; j < nPntsPerSkelPnt; j++){
                ofNoFill();
                ofSetColor(200,200,200);
                ofCircle(meshRadialPnts[i][j].x ,meshRadialPnts[i][j].y,3);
            }
        }


    ofPopMatrix();
    */



    //---------------------------------------------------------------------
    //glEnable(GL_DEPTH_TEST);
    ofPushMatrix();


    ofSetColor(255,255,255,255);
    ofEnableAlphaBlending();


        if(!drawMeshWireframes){
            imgMesh.bind(); // bind the image to begin texture mapping
                mesh.draw();
            imgMesh.unbind();
        } else {
            ofNoFill();
            ofSetLineWidth(1.0f);
            mesh.drawWireframe();
        }

        /*ofSetColor(255,0,0);
        for(int i =0; i < meshPointsAdded.size(); i++){
            ofCircle(meshPointsAdded[i].x ,meshPointsAdded[i].y,3);
        }*/

    ofDisableAlphaBlending();
    ofPopMatrix();
    //glDisable(GL_DEPTH_TEST);

    }

}
//--------------------------------------------------------------
void kinectSkelAniMesh::setImg(ofImage newimg){
    imgMesh = newimg;
}
void kinectSkelAniMesh::createTriangles(){

    triangulator.reset();

    int pntCnt = 0;

	for(int i=0; i < nPntsSkel; i++){

		triangulator.addPoint(meshSkelPnts[i]);
		pntCnt++;

		if(i >= 4){ // first 4 points not used
            for(int j =0; j < nPntsPerSkelPnt; j++){

                triangulator.addPoint(meshRadialPnts[i][j]);
                pntCnt++;
            }
        }
	}
	triangulator.triangulate();

}
//--------------------------------------------------------------
void kinectSkelAniMesh::createMesh(){

    mesh.clear();

    vector<ofxDelaunayTriangle>	triangles = triangulator.triangles;

    int pntCnt = 0;

    for(int i = 0; i < triangles.size(); i++){

        for(int j = 0; j < 3; j++){

            ofVec3f v(triangles[i].points[j].x,triangles[i].points[j].y,triangles[i].points[j].z);

            mesh.addVertex(v);
            mesh.addTexCoord(v);

            meshPointsAdded.resize(meshPointsAdded.size()+1);
            meshPointsAdded.push_back(triangles[i].points[j]);

            pntCnt++;

        }
    }

    // record the mesh vertex points for each skel id

    int numVertexPerSkelPnt = 0;

    for(int i =0; i <meshSkelPnts.size(); i++ ){

        numVertexPerSkelPnt = 0;

        for(int k =0; k <mesh.getVertices().size(); k++ ){

            //if(mesh.getVertex(k) == meshSkelPnts[i]){
            if(mesh.getVertex(k).x == meshSkelPnts[i].x && mesh.getVertex(k).y == meshSkelPnts[i].y){

                numVertexPerSkelPnt++;

                meshVertexPntsForSkelPnts[i].resize(numVertexPerSkelPnt);
                meshVertexPntsForSkelPnts[i].push_back(k);

            }
        }
    }
}
//--------------------------------------------------------------
void kinectSkelAniMesh::createRadialPnts(){

    ofPoint radialPnt;
    int angle;

    for(int i = 4; i < nPntsSkel; i++){

        ofPoint skelPnt = meshSkelPnts[i];

        for(int j =0; j < nPntsPerSkelPnt; j++){

            angle = j*60; // 6 pnts per radius

            radialPnt.x = skelPnt.x + skelPntRadius * cos(ofDegToRad(angle));
            radialPnt.y = skelPnt.y + skelPntRadius * sin(ofDegToRad(angle));

            meshRadialPnts[i].push_back(radialPnt);

        }
    }
}
//--------------------------------------------------------------
void kinectSkelAniMesh::moveRadialPnts(int skelPntID){

    ofPoint radialPnt;
    int angle;

    ofPoint skelPnt = meshSkelPnts[skelPntID];

    for(int j =0; j < nPntsPerSkelPnt; j++){

        angle = j*60; // 6 pnts per radius

        radialPnt.x = skelPnt.x + skelPntRadius * cos(ofDegToRad(angle));
        radialPnt.y = skelPnt.y + skelPntRadius * sin(ofDegToRad(angle));

        for(int i =0; i <mesh.getVertices().size(); i++ ){

            if(mesh.getVertex(i) == meshRadialPnts[skelPntID][j]){
                mesh.setVertex(i,radialPnt);


            }
        }
        meshRadialPnts[skelPntID][j] = radialPnt;
    }

}
//--------------------------------------------------------------
void kinectSkelAniMesh::mouseMoved(int x, int y){
}
//--------------------------------------------------------------
void kinectSkelAniMesh::mouseDragged(int x, int y, int button){

    if(isDragging){

        int relX, relY;
        relX = x - offsetX;
        relY = y - offsetY;

        relX = ofClamp(relX,0,meshW);
        relY = ofClamp(relY,0,meshH);

        ofPoint newPnt;
        newPnt.x = relX;
        newPnt.y = relY;

        for(int i=0; i < dragVertexPntIds.size(); i++){
            if(dragVertexPntIds[i] !=0) mesh.setVertex(dragVertexPntIds[i],newPnt);
        }

        moveRadialPnts(dragPntId);

        meshSkelPnts[dragPntId] = newPnt;

    }

}
//--------------------------------------------------------------
void kinectSkelAniMesh::mousePressed(int x, int y, int button){

    int relX, relY;
    relX = x - offsetX;
    relY = y - offsetY;

    isDragging = true;
    dragVertexPntIds.resize(0);
    int numDragPntIds = 0;

    for(int i =4; i <meshSkelPnts.size(); i++ ){

        if(ofInRange(relX, meshSkelPnts[i].x-6, meshSkelPnts[i].x+6) && ofInRange(relY, meshSkelPnts[i].y-6,meshSkelPnts[i].y+6)){
            dragPntId = i;

            for(int k =0; k <mesh.getVertices().size(); k++ ){

                if(mesh.getVertex(k).x == meshSkelPnts[dragPntId].x && mesh.getVertex(k).y == meshSkelPnts[dragPntId].y){
                    numDragPntIds++;

                    dragVertexPntIds.resize(numDragPntIds);
                    dragVertexPntIds.push_back(k);
                }
            }
        }
    }
}
//--------------------------------------------------------------
void kinectSkelAniMesh::mouseReleased(int x, int y, int button){

    isDragging = false;
}
//--------------------------------------------------------------
void kinectSkelAniMesh::setLiveSkelPoints(vector<ofPoint> pnts){

    liveSkelPnts = pnts;

    ofPoint newPnt;

    for(int i = 4; i < meshSkelPnts.size(); i++){

        int id = i-4; // first four are corners

        float relX, relY;
        relX = liveSkelPnts[id].x;
        relY = liveSkelPnts[id].y;

        newPnt.x = relX;
        newPnt.y = relY;

        //moves all the vertices for one point
        for(int k=0; k < meshVertexPntsForSkelPnts[i].size(); k++){

             if(meshVertexPntsForSkelPnts[i][k] !=0){
                mesh.setVertex(meshVertexPntsForSkelPnts[i][k],newPnt);
             }
        }
        moveRadialPnts(i);
        meshSkelPnts[i] = newPnt;

    }

    //--------------------------------------------------------------------
    int pntID;

    //top left point
    pntID = 0;
    newPnt.x = skelBoundingBox.x;
    newPnt.y = skelBoundingBox.y;

    meshSkelPnts[pntID] = newPnt;

    for(int k=0; k < meshVertexPntsForSkelPnts[pntID].size(); k++){

         if(meshVertexPntsForSkelPnts[pntID][k] !=0){
            mesh.setVertex(meshVertexPntsForSkelPnts[pntID][k],newPnt);
         }
    }

    //top right point
    pntID = 1;
    newPnt.x = skelBoundingBox.x + skelBoundingBox.width;
    newPnt.y = skelBoundingBox.y;

    meshSkelPnts[pntID] = newPnt;

    for(int k=0; k < meshVertexPntsForSkelPnts[pntID].size(); k++){
        // this is the first vertex so dont exclude it
         //if(meshVertexPntsForSkelPnts[pntID][k] !=0){
            mesh.setVertex(meshVertexPntsForSkelPnts[pntID][k],newPnt);
         //}
    }

    //bottom right point
    pntID = 2;
    newPnt.x = skelBoundingBox.x + skelBoundingBox.width;
    newPnt.y = skelBoundingBox.y + skelBoundingBox.height;

    meshSkelPnts[pntID] = newPnt;

    for(int k=0; k < meshVertexPntsForSkelPnts[pntID].size(); k++){

         if(meshVertexPntsForSkelPnts[pntID][k] !=0){
            mesh.setVertex(meshVertexPntsForSkelPnts[pntID][k],newPnt);
         }
    }

    //bottom left point
    pntID = 3;
    newPnt.x = skelBoundingBox.x;
    newPnt.y = skelBoundingBox.y + skelBoundingBox.height;

    meshSkelPnts[pntID] = newPnt;

    for(int k=0; k < meshVertexPntsForSkelPnts[pntID].size(); k++){

         if(meshVertexPntsForSkelPnts[pntID][k] !=0){
            mesh.setVertex(meshVertexPntsForSkelPnts[pntID][k],newPnt);
         }
    }
}
//--------------------------------------------------------------
void kinectSkelAniMesh::saveMeshPoints(){

    ofFile outFile;
    outFile.open("settings/meshPoints.pos", ofFile::WriteOnly, true);
    for(int i = 0; i < nPntsSkel; i++){
        outFile.write((char*) &meshSkelPnts[i], sizeof(ofPoint));
    }
    outFile.close();

}
//--------------------------------------------------------------
void kinectSkelAniMesh::readMeshPoints(){

    printf("readMeshPoints \n");

    ofFile inFile;

    ofBuffer buffer = ofBufferFromFile("settings/meshPoints.pos");
    nPntsSkel           = buffer.size()/sizeof(ofPoint);

    inFile.open("settings/meshPoints.pos", ofFile::ReadOnly, true);
    meshSkelPnts.resize(nPntsSkel);

    for(int i = 0; i < nPntsSkel; i++){
        inFile.read((char*) &meshSkelPnts[i], sizeof(ofPoint));
    }

    skelOriginX = meshSkelPnts[1].x;
    skelOriginY = meshSkelPnts[1].y;

    inFile.close();

}
//--------------------------------------------------------------
void kinectSkelAniMesh::resetPoints(){

    ofFile inFile;

    ofBuffer buffer = ofBufferFromFile("settings/meshPointsSkelKinect.pos");
    nPntsSkel       = buffer.size()/sizeof(ofPoint);

    inFile.open("settings/meshPointsSkelKinect.pos", ofFile::ReadOnly, true);
    meshSkelPnts.resize(nPntsSkel);

    for(int i = 0; i < nPntsSkel; i++){
        inFile.read((char*) &meshSkelPnts[i], sizeof(ofPoint));
    }



    inFile.close();


}
//--------------------------------------------------------------
void kinectSkelAniMesh::windowResized(int w, int h){
}
//--------------------------------------------------------------
void kinectSkelAniMesh::keyPressed(int key){

    if(key =='w'){
        drawMeshWireframes = !drawMeshWireframes;
    }

}
//--------------------------------------------------------------
void kinectSkelAniMesh::keyReleased(int key){


}
//--------------------------------------------------------------
void kinectSkelAniMesh::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void kinectSkelAniMesh::dragEvent(ofDragInfo dragInfo){
    //printf("dragEvent \n");
}

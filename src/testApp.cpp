#include "testApp.h"
#include "ofxSimpleGuiToo.h"
//--------------------------------------------------------------
void testApp::setup(){

    ofSetVerticalSync(true);
    ofSetCircleResolution(60);
    ofEnableSmoothing();


    ofSetRectMode(OF_RECTMODE_CORNER);

    aniMeshOne.setup();
    aniMeshTwo.setup();


    skelOneAssetID = 0;
    skelTwoAssetID = 0;


    useLiveData     = true;
    debug           = false;

    ofToggleFullscreen();
    ofHideCursor();
    isFullscreen = true;

    //----------------------------------------------
    skelOneBoundingBox.width    = 400;
    skelOneBoundingBox.height   = 600;


    skelTwoBoundingBox.width    = 400;
    skelTwoBoundingBox.height   = 600;

    skelOffsetX = 600;
    skelOffsetY = 250;

    //----------------------------------------------

    skelOnePnts.resize(20);
    skelTwoPnts.resize(20);



    logoImg.loadImage("ui/animatedMeLogo.png");

    //----------------------------------------------

    //string filename = "files/rec30fps_12_29_15-56-31-1.knct";
    //string filename = "files/rec30fps_02_01_17-05-21-1.knct";
    //string filename = "files/rec30fps_02_15_13-55-29-1.knct";
    //string filename = "files/rec30fps_12_29_16-24-23-1.knct";
    string filename = "files/rec30fps_02_15_13-55-29-1.knct";

    loader          = new ofxMSKinectSkelDataReader(filename.c_str());
	fileLoaded      = true;
	loader->start();


	MSkinect.setup();


	kinectDrawX     = 0;
	kinectDrawY     = 0;
    kinectScale     = 1.0f;

    characterNameOne.setup();
    characterNameOne.setCharacterName("character one", "creator one");

    characterNameTwo.setup();
    characterNameTwo.setCharacterName("character two", "creator two");


    footerMsgGraphics.setup();


    characterOneChangeDetector.setup();
    characterTwoChangeDetector.setup();

    charAssets.setup();

    assetManagerOne.setup();
    assetManagerTwo.setup();

	//----------------------------------------------


    gui.addSlider("Offset X", skelOffsetX, 0, ofGetScreenWidth()).setSize(260,40);
    gui.addSlider("Offset Y", skelOffsetY, 0, ofGetScreenHeight()).setSize(260,40);
    gui.addSlider("kinectScale", kinectScale, 0.25f, 2.5f).setSize(260,40);

    gui.loadFromXML();
    gui.show();

}

//--------------------------------------------------------------
void testApp::update(){

    charAssets.update();
    assetManagerOne.update();
    assetManagerTwo.update();

    if(useLiveData){
        MSkinect.update();

        if(MSkinect.nSkeletons > 0){

            skelOnePnts                 = MSkinect.getAllPoints(0);

            skelOneBoundingBox.x        = MSkinect.getStomachPoint(0).x - skelOneBoundingBox.width*.5;
            skelOneBoundingBox.y        = MSkinect.getStomachPoint(0).y - skelOneBoundingBox.height*.5;

            skelOneBoundingBox.y        +=50;

            characterNameOne.targetX    = MSkinect.getHeadPoint(0).x ;
            characterNameOne.targetY    = MSkinect.getHeadPoint(0).y - 300;


            characterOneChangeDetector.update(MSkinect.getLeftHandPoint(0),MSkinect.getRightHandPoint(0),MSkinect.getHeadPoint(0));

            //-------------------------------
            assetManagerOne.isRequestingChange(characterOneChangeDetector.moveEffective);

            if(characterOneChangeDetector.moveEffective){
                characterNameOne.isChanging = true;
            } else {
                characterNameOne.isChanging = false;
            }

            if(assetManagerOne.doChange){
                assetManagerOne.isRequestingChange(false);
                changeAssets(0);
            }

            //---------------------------------------


            if(MSkinect.nSkeletons > 1){

                skelTwoPnts                 = MSkinect.getAllPoints(1);
                skelTwoBoundingBox.x        = MSkinect.getStomachPoint(1).x - skelTwoBoundingBox.width*.5;
                skelTwoBoundingBox.y        = MSkinect.getStomachPoint(1).y - skelTwoBoundingBox.height*.5;

                skelTwoBoundingBox.y        +=50;

                characterNameTwo.targetX    = MSkinect.getHeadPoint(1).x ;
                characterNameTwo.targetY    = MSkinect.getHeadPoint(1).y - 300 ;

                characterTwoChangeDetector.update(MSkinect.getLeftHandPoint(1),MSkinect.getRightHandPoint(1),MSkinect.getHeadPoint(1));

                //-------------------------------------------------------------------

                assetManagerTwo.isRequestingChange(characterTwoChangeDetector.moveEffective);

                if(characterTwoChangeDetector.moveEffective){
                    characterNameTwo.isChanging = true;
                } else {
                    characterNameTwo.isChanging = false;
                }

                if(assetManagerTwo.doChange){

                    assetManagerTwo.isRequestingChange(false);
                    changeAssets(1);
                }

                //-------------------------------------------------------------------
            }
        }
    }

    //--------------------------------------------------
    if(fileLoaded && !useLiveData){

	    loader->readTo();
        loader->updatePnts();
        pos1                = loader->getPoints(0);
        pos2                = loader->getPoints(1);

        //------------------------------------------------------------------

        skelOnePnts[0] = ofVec3f(pos1[0],pos1[1]);

        skelOnePnts[1] = ofVec3f(pos1[3],pos1[4]);
        skelOnePnts[2] = ofVec3f(pos1[6],pos1[7]);
        skelOnePnts[3] = ofVec3f(pos1[9],pos1[10]);

        skelOnePnts[4] = ofVec3f(pos1[12],pos1[13]);
        skelOnePnts[5] = ofVec3f(pos1[15],pos1[16]);
        skelOnePnts[6] = ofVec3f(pos1[18],pos1[19]);
        skelOnePnts[7] = ofVec3f(pos1[21],pos1[22]);

        skelOnePnts[8] = ofVec3f(pos1[24],pos1[25]);
        skelOnePnts[9] = ofVec3f(pos1[27],pos1[28]);
        skelOnePnts[10] = ofVec3f(pos1[30],pos1[31]);
        skelOnePnts[11] = ofVec3f(pos1[33],pos1[34]);

        skelOnePnts[12] = ofVec3f(pos1[36],pos1[37]);
        skelOnePnts[13] = ofVec3f(pos1[39],pos1[40]);
        skelOnePnts[14] = ofVec3f(pos1[42],pos1[43]);
        skelOnePnts[15] = ofVec3f(pos1[45],pos1[46]);

        skelOnePnts[16] = ofVec3f(pos1[48],pos1[49]);
        skelOnePnts[17] = ofVec3f(pos1[51],pos1[52]);
        skelOnePnts[18] = ofVec3f(pos1[54],pos1[55]);
        skelOnePnts[19] = ofVec3f(pos1[57],pos1[58]);

        //-----------------------------------------

        skelTwoPnts[0] = ofVec3f(pos2[0],pos2[1]);
        skelTwoPnts[1] = ofVec3f(pos2[3],pos2[4]);
        skelTwoPnts[2] = ofVec3f(pos2[6],pos2[7]);
        skelTwoPnts[3] = ofVec3f(pos2[9],pos2[10]);

        skelTwoPnts[4] = ofVec3f(pos2[12],pos2[13]);
        skelTwoPnts[5] = ofVec3f(pos2[15],pos2[16]);
        skelTwoPnts[6] = ofVec3f(pos2[18],pos2[19]);
        skelTwoPnts[7] = ofVec3f(pos2[21],pos2[22]);

        skelTwoPnts[8] = ofVec3f(pos2[24],pos2[25]);
        skelTwoPnts[9] = ofVec3f(pos2[27],pos2[28]);
        skelTwoPnts[10] = ofVec3f(pos2[30],pos2[31]);
        skelTwoPnts[11] = ofVec3f(pos2[33],pos2[34]);

        skelTwoPnts[12] = ofVec3f(pos2[36],pos2[37]);
        skelTwoPnts[13] = ofVec3f(pos2[39],pos2[40]);
        skelTwoPnts[14] = ofVec3f(pos2[42],pos2[43]);
        skelTwoPnts[15] = ofVec3f(pos2[45],pos2[46]);

        skelTwoPnts[16] = ofVec3f(pos2[48],pos2[49]);
        skelTwoPnts[17] = ofVec3f(pos2[51],pos2[52]);
        skelTwoPnts[18] = ofVec3f(pos2[54],pos2[55]);
        skelTwoPnts[19] = ofVec3f(pos2[57],pos2[58]);

        //-----------------------------------------
        //-------------------------------------------------------------------------

        skelOneBoundingBox.x = pos1[3] - skelOneBoundingBox.width*.5;
        skelOneBoundingBox.y = pos1[4] - skelOneBoundingBox.height*.5;
        //--------------------------------------------------------------------------

        skelTwoBoundingBox.x = pos2[3] - skelTwoBoundingBox.width*.5;
        skelTwoBoundingBox.y = pos2[4] - skelTwoBoundingBox.height*.5;

	}

	aniMeshOne.setLiveSkelPoints(skelOnePnts);
    aniMeshTwo.setLiveSkelPoints(skelTwoPnts);

    aniMeshOne.skelBoundingBox = skelOneBoundingBox;
    aniMeshTwo.skelBoundingBox = skelTwoBoundingBox;

    //--------------------------------------------------------------------------

	aniMeshOne.update();
	aniMeshTwo.update();

    aniMeshOne.meshOffsetX = skelOffsetX;
    aniMeshOne.meshOffsetY = skelOffsetY;

    aniMeshTwo.meshOffsetX = skelOffsetX;
    aniMeshTwo.meshOffsetY = skelOffsetY;


    characterNameOne.update();
    characterNameTwo.update();

}

//--------------------------------------------------------------
void testApp::draw(){

    ofBackgroundGradient(ofColor::gray, ofColor::black,OF_GRADIENT_CIRCULAR);

    //------------------------------------------------------------
    // loaded skel data
    //------------------------------------------------------------

    if(fileLoaded && debug && !useLiveData){

        ofPushMatrix();
        ofTranslate(skelOffsetX,skelOffsetY,0.0f);

        // Points ////////////////////////////////////////////////////////////
        // seleton 1

        int id;

        ofNoFill();

        for(int i = 0; i < (21*3); i+=3){ //(20*3); 20 points with x,y,z

            if(pos1[i] > 0.0 && pos1[i+1] > 0.0){

                id = floor(i/3);

                ofSetHexColor(0xff0000);
                ofRect(pos1[i]-8, pos1[i+1]-8, pos1[i+2], 16,16);

                ofSetHexColor(0xffffff);
                ofDrawBitmapString(ofToString(id), pos1[i]-8 ,pos1[i+1]+8, pos1[i+2]);
            }
        }
        // seleton 1

        for(int i = 0; i < (20*3); i+=3){ //(20*3); 20 points with x,y,z

            if(pos2[i] > 0.0 && pos2[i+1] > 0.0){

                id = floor(i/3);

                ofSetHexColor(0xff0000);
                ofRect(pos2[i]-5, pos2[i+1]-5,pos2[i+2], 16,16);

                ofSetHexColor(0xffffff);
                ofDrawBitmapString(ofToString(id), pos2[i]-8 ,pos2[i+1]+8,pos2[i+2]);

            }

        }

        ofPopMatrix();

    }

    //------------------------------------------------------------
    // meshes
    //------------------------------------------------------------

    ofPushMatrix();
    ofTranslate(skelOffsetX,skelOffsetY,0.0f);
    ofScale(kinectScale,kinectScale,1.0f);


        //--------------------------------------------------------------------

        if(MSkinect.nSkeletons > 0) {

            ofSetColor(200,200,200,255);
            ofSetLineWidth(0.5f);
            ofLine(characterNameOne.curX, characterNameOne.curY + 100, MSkinect.getHeadPoint(0).x,MSkinect.getHeadPoint(0).y - 100 );

            ofNoFill();
            ofSetLineWidth(2.5f);

            ofCircle(characterNameOne.curX, characterNameOne.curY + 95, 6);

            //--------------------------------------------------------------------

            aniMeshOne.draw();
            characterNameOne.draw();

        }

        if(MSkinect.nSkeletons > 1) {

            ofSetColor(200,200,200,255);
            ofSetLineWidth(0.5f);
            ofLine(characterNameTwo.curX, characterNameTwo.curY + 100, MSkinect.getHeadPoint(1).x,MSkinect.getHeadPoint(1).y - 100 );

            ofNoFill();
            ofSetLineWidth(2.5f);

            ofCircle(characterNameTwo.curX, characterNameTwo.curY + 95, 6);

            //--------------------------------------------------------------------

            aniMeshTwo.draw();
            characterNameTwo.draw();
        }

        if(debug){

            ofDrawBitmapString("N Skels "+ofToString(MSkinect.nSkeletons), 20,20);

            if(characterOneChangeDetector.moveEffective){
                ofDrawBitmapString("hands up skel one! ", 200,200);
            }else{
                ofDrawBitmapString("hands down skel one :( ", 200,200);
            }

            if(characterTwoChangeDetector.moveEffective){
                ofDrawBitmapString("hands up skel two! ", 200,240);
            }else{
                ofDrawBitmapString("hands down skel two :( ", 200,240);
            }
            // SKEL 1 Bounding box

            ofSetHexColor(0x0000ff);
            ofNoFill();
            ofRect(skelOneBoundingBox);

            ofSetHexColor(0xff0000);
            ofLine(
                   skelOneBoundingBox.x,
                   skelOneBoundingBox.y+ skelOneBoundingBox.height*.5,
                   skelOneBoundingBox.x+skelOneBoundingBox.width,
                   skelOneBoundingBox.y+ skelOneBoundingBox.height*.5);

            ofSetHexColor(0xff0000);
            ofLine(
                   skelOneBoundingBox.x+skelOneBoundingBox.width*.5,
                   skelOneBoundingBox.y,
                   skelOneBoundingBox.x+skelOneBoundingBox.width*.5,
                   skelOneBoundingBox.y+ skelOneBoundingBox.height);



                   // SKEL 1 Bounding box

            ofSetHexColor(0x0000ff);
            ofNoFill();
            ofRect(skelTwoBoundingBox);


            ofSetHexColor(0xff0000);
            ofLine(
                   skelTwoBoundingBox.x,
                   skelTwoBoundingBox.y+ skelTwoBoundingBox.height*.5,
                   skelTwoBoundingBox.x+skelTwoBoundingBox.width,
                   skelTwoBoundingBox.y+ skelTwoBoundingBox.height*.5);

            ofSetHexColor(0xff0000);
            ofLine(
                   skelTwoBoundingBox.x+skelTwoBoundingBox.width*.5,
                   skelTwoBoundingBox.y,
                   skelTwoBoundingBox.x+skelTwoBoundingBox.width*.5,
                   skelTwoBoundingBox.y+ skelTwoBoundingBox.height);

        }

    ofPopMatrix();

    if(debug) gui.draw();

    //----------------------------------------------------------
    ofEnableAlphaBlending();
    ofSetColor(255,255,255,255);
        logoImg.draw((ofGetWidth()-logoImg.width)*.5, 30);
    ofDisableAlphaBlending();


    footerMsgGraphics.draw();



}

//--------------------------------------------------------------
void testApp::changeAssets(int skelID){

    string charName;
    string creatorName;
    ofImage img;

    if(skelID == 0){

        skelOneAssetID++;
        if(skelOneAssetID >= charAssets.totalNumAssets ) skelOneAssetID = 0;

        charName    = charAssets.getCharacterName(skelOneAssetID);
        creatorName = charAssets.getCreatorName(skelOneAssetID);
        img         = charAssets.getImage(skelOneAssetID);

        characterNameOne.setCharacterName(charName,creatorName);
        aniMeshOne.setImg(img);

    }else{

        skelTwoAssetID++;
        if(skelTwoAssetID >= charAssets.totalNumAssets ) skelTwoAssetID = 0;

        charName    = charAssets.getCharacterName(skelTwoAssetID);
        creatorName = charAssets.getCreatorName(skelTwoAssetID);
        img         = charAssets.getImage(skelTwoAssetID);

        characterNameTwo.setCharacterName(charName,creatorName);
        aniMeshTwo.setImg(img);

    }

    printf("skelOneAssetID %i skelTwoAssetID %i \n",skelOneAssetID,skelTwoAssetID);
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){

    aniMeshOne.keyPressed(key);
    aniMeshTwo.keyPressed(key);

    if(key == 'd' || key == 'D') debug = !debug;

    debug ? gui.show() : gui.hide();

    if(key == 'f' || key == 'F'){
        isFullscreen = !isFullscreen;
        ofToggleFullscreen();
    }

    if(key == 'p') changeAssets(0);
    if(key == 'o') changeAssets(1);

    if(key=='r') charAssets.loadData();

    ofShowCursor();
    if(isFullscreen) ofHideCursor();

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
}
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

    //aniMeshOne.mouseDragged(x, y, button);
    //aniMeshTwo.mouseDragged(x, y, button);

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    //aniMeshOne.mousePressed(x, y, button);
    //aniMeshTwo.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    //aniMeshOne.mouseReleased(x, y, button);
    //aniMeshTwo.mouseReleased(x, y, button);
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

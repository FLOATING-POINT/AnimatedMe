#pragma once

#include "ofMain.h"
#include "kinectSkelAniMesh.h"

#include "ofxMSKinectSkelDataReader.h"
#include "dataContainer.h"
#include "MSKinectWrapper.h"
#include "characterName.h"
#include "ofxHandsUpMoveDetector.h"
#include "footerMsg.h"
#include "characterAssets.h"
#include "skelAssetManager.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void changeAssets(int skelID);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);



		bool                            useLiveData;
		bool                            isFullscreen;

		ofImage                         logoImg;
		MSKinectWrapper                 MSkinect;

        bool                            debug;
		kinectSkelAniMesh               aniMeshOne;
		kinectSkelAniMesh               aniMeshTwo;

		//-------------------------------------------------

		vector<ofVec3f>                 skelOnePnts;
		vector<ofVec3f>                 skelTwoPnts;

		//-------------------------------------------------

        int                             skelOffsetX, skelOffsetY;
        float                           kinectDrawX, kinectDrawY;
        float                           kinectScale;
		//-------------------------------------------------

		ofRectangle                     skelOneBoundingBox;
		ofRectangle                     skelTwoBoundingBox;

		//-------------------------------------------------


		characterName                   characterNameOne;
		characterName                   characterNameTwo;
		int                             skelOneAssetID;
		int                             skelTwoAssetID;

		ofxHandsUpMoveDetector          characterOneChangeDetector;
		ofxHandsUpMoveDetector          characterTwoChangeDetector;

		//-------------------------------------------------

		footerMsg                       footerMsgGraphics;

		characterAssets                 charAssets;

		skelAssetManager                assetManagerOne;
		skelAssetManager                assetManagerTwo;


		ofxMSKinectSkelDataReader *loader;
		bool            fileLoaded;

        float * pos1;
        float * pos2;
};

#ifndef _HANDS_UP_DETECTOR
#define _HANDS_UP_DETECTOR

#include "ofMain.h"

class ofxHandsUpMoveDetector{

	public:
		void setup();
		void update(ofVec3f _handLeftPnt, ofVec3f _handRightPnt, ofVec3f _headPoint);
		void draw();

		bool    moveDetected;
		bool    moveEffective;
		float     effectiveDur;
        float     detectedStart;

		int hTolerance; // horizontal tolerance

		ofVec3f handLeftPnt,handRightPnt;
		ofVec3f headPnt, waistPnt;
		ofVec3f leftShoulderPnt, rightShoulderPnt;

		int shoulderWidth;
		float shoulderWidthTolerance;


};

#endif

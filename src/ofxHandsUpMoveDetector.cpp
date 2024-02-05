#include "ofxHandsUpMoveDetector.h"

//--------------------------------------------------------------
void ofxHandsUpMoveDetector::setup(){

    moveDetected            = false;
    moveEffective           = false;
    detectedStart           = 0.0f;
    effectiveDur            = 2.0f;

}

//--------------------------------------------------------------
void ofxHandsUpMoveDetector::update(ofVec3f _handLeftPnt, ofVec3f _handRightPnt, ofVec3f _headPoint){


    if(_handLeftPnt.y < _headPoint.y && _handRightPnt.y < _headPoint.y){
        if(!moveDetected){
            moveDetected = true;
            detectedStart = int(ofGetElapsedTimeMillis()/1000);
        }

        if(moveDetected){
            int curSecs = int(ofGetElapsedTimeMillis()/1000);
            if(curSecs - detectedStart > effectiveDur){

                moveEffective = true;
            }
        }


    } else {
        moveEffective = false;
        moveDetected  = false;
    }


}

//--------------------------------------------------------------
void ofxHandsUpMoveDetector::draw(){

}


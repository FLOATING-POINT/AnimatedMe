#include "footerMsg.h"

//--------------------------------------------------------------
void footerMsg::setup(){

    img.loadImage("ui/footerMsg.png");

}

//--------------------------------------------------------------
void footerMsg::update(){

}

//--------------------------------------------------------------
void footerMsg::draw(){

    ofEnableAlphaBlending();
    ofSetColor(255,255,255,255);
    ofPushMatrix();
    ofTranslate((ofGetWidth()-img.width)*0.5, ofGetHeight() - (img.height+10));
        img.draw(0,0);
    ofPopMatrix();
    ofDisableAlphaBlending();


}

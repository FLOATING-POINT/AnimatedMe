#include "characterName.h"

//--------------------------------------------------------------
void characterName::setup(){

    curX            = 0;
    curY            = 0;
    targetX         = 0;
    targetY         = 0;

	alpha           = 255;

    characterName       = "Character One name";
    creatorName         = "Creator One name";

    isChanging          = false;

    characterNameTxt.defaultFont.setGlobalDpi(72);
    characterNameTxt.init("fonts/DroidSans-Bold.ttf", 30);
    characterNameTxt.defaultFont.setLetterSpacing(0.9f);
    characterNameTxt.defaultFont.setLineHeight(26);
    characterNameTxt.defaultFont.setSpaceSize(0.1f);
    characterNameTxt.setText(characterName);
    characterNameTxt.wrapTextX(300);

    creatorNameTxt.defaultFont.setGlobalDpi(72);
    creatorNameTxt.init("fonts/DroidSans.ttf", 18);
    //creatorNameTxt.defaultFont.setLetterSpacing(0.9f);
    creatorNameTxt.defaultFont.setLineHeight(16);
    creatorNameTxt.defaultFont.setSpaceSize(0.1f);
    creatorNameTxt.setText(creatorName);
    creatorNameTxt.wrapTextX(300);

    changingTxt.defaultFont.setGlobalDpi(72);
    changingTxt.init("fonts/DroidSans.ttf", 18);
    //creatorNameTxt.defaultFont.setLetterSpacing(0.9f);
    changingTxt.defaultFont.setLineHeight(16);
    changingTxt.defaultFont.setSpaceSize(0.1f);
    changingTxt.setText("Your character is about to change!");
    changingTxt.wrapTextX(300);


    setCharacterName(characterName, creatorName);
}

//--------------------------------------------------------------
void characterName::update(){

    curX += (targetX - curX)*0.05f;
    curY += (targetY - curY)*0.05f;

}

//--------------------------------------------------------------
void characterName::draw(){


    ofEnableAlphaBlending();
    ofSetColor(222,255,0,alpha);
    ofPushMatrix();
    ofTranslate(curX,curY,0.0f);

        characterNameTxt.drawCenter(0,0);
        creatorNameTxt.drawCenter(0,0 + characterNameTxt.getHeight()+10);

        ofSetColor(255,255,255,alpha);
        if(isChanging) changingTxt.drawCenter(0,0 + characterNameTxt.getHeight()+ creatorNameTxt.getHeight()+20);

    ofPopMatrix();
    ofDisableAlphaBlending();


}
//--------------------------------------------------------------

void characterName::setCharacterName(string name, string creator){

    characterName   = name;
    creatorName     = "Created by: "+creator;

    characterNameTxt.setText(characterName);
    characterNameTxt.wrapTextX(300);

    creatorNameTxt.setText(creatorName);
    creatorNameTxt.wrapTextX(300);

}

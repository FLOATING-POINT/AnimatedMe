#pragma once

#include "ofMain.h"
#include "ofxTextSuite.h"

class characterName{

	public:
		void setup();
		void update();
		void draw();
		void setCharacterName(string name, string creator);

		string                          characterName;
		string                          creatorName;

		ofxTextBlock                    characterNameTxt;
		ofxTextBlock                    creatorNameTxt;
		ofxTextBlock                    changingTxt;

		float                           curX,curY,targetX, targetY;
		int                             alpha;

		ofRectangle                    characterNameRect;
		ofRectangle                    creatorNameRect;

		bool                            isChanging;


};



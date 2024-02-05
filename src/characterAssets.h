#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "remoteImage.h"

class characterAssets{

	public:
		void setup();
		void update();
		void draw();
		void loadData();
		void urlResponse(ofHttpResponse &httpResponse);
		string getCharacterName(int id);
		string getCreatorName(int id);
		ofImage getImage(int id);


		int                             lastAssetsID;
		int                             maxNumAssets;
		int                             totalNumAssets;
		bool                            isLoading;
		bool                            hasLoaded;

		string                          assetURL;
		vector< vector< string > >      assetNames;
		remoteImage*                    imgs;

		//ofxXmlSettings                  XML;
};



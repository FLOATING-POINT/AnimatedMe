#pragma once

#include "ofMain.h"
#include "ofURLFileLoader.h"

class remoteImage{

	public:
		void setup(int _id);
		void load(string url);
		void urlResponse(ofHttpResponse & response);

		ofImage     img;
		int         id;
		bool        loading;
		bool        loaded;


};


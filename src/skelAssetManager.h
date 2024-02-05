#pragma once

#include "ofMain.h"

class skelAssetManager{

	public:
		void setup();
		void update();
		void isRequestingChange(bool change);

        float         secsBetweenChange;
		float         secsChangeStart;

		bool        doChange;
		bool        requestChange;
		bool        monitoringChange;
};

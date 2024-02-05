#include "remoteImage.h"

//--------------------------------------------------------------
void remoteImage::setup(int _id){

    id      = _id;

    loaded  = false;
    loading = false;
	ofRegisterURLNotification(this);


}

//--------------------------------------------------------------
void remoteImage::load(string url){

    ofLoadURLAsync(url,ofToString(id));
	loading = true;
}


//--------------------------------------------------------------
void remoteImage::urlResponse(ofHttpResponse & response){

	if(response.status == 200 && response.request.name == ofToString(id)){

		img.loadImage(response.data);
		loading = false;
		loaded  = true;


	}
}

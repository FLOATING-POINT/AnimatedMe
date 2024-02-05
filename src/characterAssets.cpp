#include "characterAssets.h"

//--------------------------------------------------------------
void characterAssets::setup(){

    lastAssetsID        = 0;
    totalNumAssets      = 0;
    maxNumAssets        = 500;
    assetURL            = "http://animatedMe.co.uk/getAssets.php";
    isLoading           = false;
    hasLoaded           = false;


    imgs                = new remoteImage[maxNumAssets];

    ofRegisterURLNotification(this);

}

//--------------------------------------------------------------
void characterAssets::update(){

    if(!isLoading && ofGetFrameNum() % (60*60*5) == 0 || ofGetFrameNum() == 120 ) loadData();

}
//--------------------------------------------------------------
void characterAssets::loadData(){

    isLoading           = true;

    string URL;
    URL                 = assetURL+"?id="+ofToString(lastAssetsID);


    ofLoadURLAsync(URL,"loadxml");

    printf("loadData \n",URL.c_str());

}

//--------------------------------------------------------------
void characterAssets::draw(){

}
//--------------------------------------------------------------

void characterAssets::urlResponse(ofHttpResponse &httpResponse){

    isLoading           = false;
    ofxXmlSettings  XML;

    if(httpResponse.status==200 && httpResponse.request.name == "loadxml"){  // i.e is it ok
        XML.loadFromBuffer(httpResponse.data);

        int numContainer = XML.getNumTags("assets");

        if(numContainer > 0){

            XML.pushTag("assets");
            int numAssets = XML.getNumTags("asset");

            printf("numAssets %i \n",numAssets);

            for(int i =0; i < numAssets; i++){

                int id                  = XML.getValue("asset:id", 0, i);
                string creatorName      = XML.getValue("asset:crname", "", i);
                string characterName    = XML.getValue("asset:charname", "", i);
                string imgURL           = XML.getValue("asset:imgurl", "", i);

                //-------------------------------------------------------------------

                int newVecID = assetNames.size()+1;
                assetNames.resize(newVecID);

                assetNames[newVecID-1].resize(2);
                assetNames[newVecID-1][0] = creatorName;
                assetNames[newVecID-1][1] = characterName;

                imgs[newVecID-1].setup(id);
                imgs[newVecID-1].load(imgURL);

                if(i == numAssets-1) lastAssetsID = id;


                totalNumAssets++;

            }
        }
    }

    hasLoaded = true;
}
//--------------------------------------------------------------
string characterAssets::getCharacterName(int id){
    return assetNames[id][1];
}
//--------------------------------------------------------------
string characterAssets::getCreatorName(int id){
    return assetNames[id][0];
}
//--------------------------------------------------------------
ofImage characterAssets::getImage(int id){
    return imgs[id].img;
}

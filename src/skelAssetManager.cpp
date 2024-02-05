#include "skelAssetManager.h"

//--------------------------------------------------------------
void skelAssetManager::setup(){


    secsBetweenChange   = 2.0f;
    secsChangeStart     = 0;
    doChange            = false;
    monitoringChange       = false;
}

//--------------------------------------------------------------
void skelAssetManager::update(){

    if(monitoringChange){

        if(ofGetElapsedTimef()- secsChangeStart > secsBetweenChange){
            doChange = true;
        }
    }
}

//--------------------------------------------------------------
void skelAssetManager::isRequestingChange(bool change){

    if(change && !monitoringChange){
        monitoringChange = true;
        secsChangeStart = ofGetElapsedTimef();

    }else if(!change){
        doChange         = false;
        monitoringChange = false;
    }
}

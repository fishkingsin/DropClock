/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  testApp.h, created by Marek Bereza on 09/01/2012.
 */

#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

// A simple little Data class. This is were
// you can store anything you want.
class Data {
public:
	ofColor color;
	string		id;
};


// A Custom Particle extedning the box2d circle
class CustomParticle : public ofxBox2dCircle {
	
public:
	
	void setupTheCustomData() {
		setData(new Data());
		Data * theData = (Data*)getData();
		theData->color.setHsb(ofMap(ofGetHours(),0,24,0,360)+ofRandom(-10,10), 255, 255, 255);
        theData->id = ofToString(ofGetSeconds());
	}
	
	void draw() {
		Data* theData = (Data*)getData();
		if(theData) {
			float radius = getRadius();
			ofPushMatrix();
			ofTranslate(getPosition());
			ofRotateZ(getRotation());
			ofSetColor(theData->color);
			ofFill();
			ofCircle(0, 0, radius);
            ofSetColor(255);
            ofDrawBitmapString(theData->id, -5, 5);
			ofPopMatrix();
		}
	}
    
    
};

class testApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    ofxBox2d						box2d;			  //	the box2d world
	vector		<CustomParticle>	circles;		  //	default box2d circles
	vector		<ofxBox2dRect>		boxes;			  //	defalut box2d rects
    vector <ofxBox2dPolygon>	polyLines;
    ofTrueTypeFont font;
    void createPolygon(string str , ofTrueTypeFont &font , vector <ofxBox2dPolygon>	&polyLines , ofxBox2d &box2d);
};

/**
 *  testApp.cpp
 *
 *  Created by Marek Bereza on 09/01/2012.
 */

#include "testApp.h"
int currentMinute = 0;
int currentSecond = 0;
void testApp::createPolygon(string str , ofTrueTypeFont &font , vector <ofxBox2dPolygon>	&polyLines , ofxBox2d &box2d)
{
    vector<ofTTFCharacter> chars = font.getStringAsPoints(str);
    ofRectangle rect = font.getStringBoundingBox(str, ofGetWidth()*0.5, (ofGetHeight()*0.5)-248);
    rect.x -= rect.width*0.5;
    for (int i = 0 ; i < chars.size(); i++) {
        vector<ofPolyline> polylines =  chars[i].getOutline();
        ofLogVerbose(ofToString(polylines.size()));
        ofxBox2dPolygon poly;
        
        for(int j = 0 ; j < polylines.size(); j++)
        {
            
            vector<ofPoint> ptns = polylines[j].getVertices();
            for(int k = 0 ; k < ptns.size(); k++)
            {
                ofLogVerbose("X: "+ofToString(ptns[k].x)+" Y : "+ofToString(ptns[k].y));
                poly.addVertex( ptns[k].x+rect.x,ptns[k].y+ rect.y+rect.height);
            }
            poly.addVertex( ptns[0].x+rect.x,ptns[0].y+ rect.y+rect.height);
        }
        
        poly.setPhysics(0.15, 0.5,0.5);
        poly.create(box2d.getWorld());
        poly.setRotation(ofRandom(TWO_PI));
        polyLines.push_back(poly);
        
    }
    
}
void testApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0);
	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createBounds();
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
    font.loadFont("Impact.ttf", 248, true, true, true);
    for(int i = 0 ; i < 300 ;i++)
    {
        CustomParticle c;
        
        c.setPhysics(0.15, 0.5, 0.5);
        c.setup(box2d.getWorld(), ofRandomf()*ofGetWidth(),10, ofRandom(10, 40));
        c.setupTheCustomData();
        circles.push_back(c);
    }
    
}

void testApp::update() {
    if(ofGetMinutes()!=currentMinute)
    {
        string _str = ofToString(ofGetHours(),2)+":"+ofToString(ofGetMinutes(),2);
        string str = "";
        for(int i = 0 ; i < _str.length() ;i++)
        {
            str += std::string(1, _str[i]);
            str += " ";
        }
        
        for (int i=0; i< polyLines.size(); i++) {
            polyLines[i].destroy();
        }
        while(polyLines.size()>0)
        {
            polyLines.pop_back();
        }
        createPolygon(str, font ,polyLines , box2d);
        currentMinute = ofGetMinutes();
        //        vector<CustomParticle>::iterator it;
        //        if(circles.size()>60)
        //        {
        //            for (int i = 0 ; i < 60; i++) {
        //                it = circles.begin();
        //                (*it).destroy();
        //                circles.erase(it);
        //
        //
        //            }
        //        }
        
	}
    else if(ofGetSeconds()!=currentSecond)
    {
        if(circles.size()>1)
        {
            vector<CustomParticle>::iterator it;
            //            for (int i = 0 ; i < 60; i++) {
            it = circles.begin();
            (*it).destroy();
            circles.erase(it);
            
            
            //            }
        }
        CustomParticle c;
        
		c.setPhysics(0.15, 0.05, 0.5);
		c.setup(box2d.getWorld(),ofGetWidth()*0.5,50, ofRandom(15, 40));
        c.setupTheCustomData();
		circles.push_back(c);
        
        currentSecond = ofGetSeconds();
	}
    box2d.update();
    
}

void testApp::draw() {
    ofSetColor(255,255,255);
    //	ofRect(pos.x, pos.y, 100, 100);
    
	for(int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetHexColor(0xf6c738);
		circles[i].draw();
	}
	
	for(int i=0; i<boxes.size(); i++) {
		ofFill();
		ofSetHexColor(0xBF2545);
		boxes[i].draw();
	}
    for (int i=0; i<polyLines.size(); i++) {
        ofFill();
		ofSetHexColor(0xFFFFFF);
		polyLines[i].draw();
	}
	// draw the ground
//	box2d.drawGround();
    
}
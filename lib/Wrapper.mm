/**
 *  Wrapper.cpp
 *
 *  Created by Marek Bereza on 09/01/2012.
 */

#include "Wrapper.h"
#include "ofxAppMacScreenSaver.h"
#include "main.h"
#include <string>
#import <AppKit/AppKit.h>
using namespace std;

ofxAppMacScreenSaver *screensaver;
string dataPath = "";

void init(const char *resPath) {
	screensaver = ofxScreensaver_main();
	dataPath = resPath;
}
void setup() {

	NSScreen *mainScreen = [NSScreen mainScreen];

	screensaver->setupOpenGL([mainScreen frame].size.width, [mainScreen frame].size.height, 0, dataPath);//, <#int h#>, <#int screenMode#>)
	
	screensaver->initializeWindow();
	
}
void display() {
	screensaver->display();
}
void resize_cb(int w, int h) {
	screensaver->resize_cb(w, h);
}
void idle_cb() {
	screensaver->idle_cb();
}
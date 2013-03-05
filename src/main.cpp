/*
 * main.cpp
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  Sets up the OpenGL window, sets it to full
 * screen and runs the flashtrack application.
 *
 */

#include "ofMain.h"
#include "flashtrack.h"
#include "ofAppGlutWindow.h"

int main() {

    ofAppGlutWindow window;
    window.setFullscreen(true);
    ofSetupOpenGL(&window, window.getScreenSize().x, window.getScreenSize().y, OF_FULLSCREEN); // <-------- setup the GL context

    ofRunApp(new flashtrack());
}

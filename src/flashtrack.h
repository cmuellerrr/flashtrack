/*
 * flashtrack.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  Sets up the tracker and gives control
 * over to the screen manager.
 *
 */

#ifndef _FLASHTRACK_H
#define _FLASHTRACK_H

#include "ofMain.h"
#include "tracker.h"
#include "screenManager.h"

class flashtrack : public ofBaseApp {

    public:

        flashtrack();
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void resized(int w, int h);
    
    private:

        screenManager manager;
        tracker _tracker;

        ofSoundPlayer bgMusic;
};

#endif

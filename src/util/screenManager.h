/*
 * screenManager.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  A screen manager class.  Handles the transition
 * between screens in the application.  Only the active 
 * application is handled while all others remain idle.
 *
 */

#pragma once
//#ifndef _SCREEN_MANAGER_H
//#define _SCREEN_MANAGER_H

#include "tracker.h"
#include "title.h"
#include "selection.h"
#include "creator.h"
#include "configuration.h"
#include "ofxFadable.h"


enum{TITLE, SELECT, CREATE, CONFIG};

class screenManager : public ofBaseApp {

    public:

        screenManager();
        void setup(tracker* t);
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);

        void setMode(int newMode);
   
    private:

        tracker* _tracker;
        title titleApp;
        selection selectApp;
        creator createApp;
        configuration configApp;
        ofxFadableRect fader;

        int mode, nextMode;
        bool transition;
};

//#endif

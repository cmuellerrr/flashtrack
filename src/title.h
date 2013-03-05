/*
 * title.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  The title screen of the application.
 *
 */

#ifndef _TITLE_H
#define _TITLE_H

#include "ofMain.h"
#include "tracker.h"
#include "gui.h"

class title : public ofBaseApp {

    public:

        title();
        void setup(tracker* t, ofBaseApp* p);
        void update();
        void draw();

        void mousePressed(int x, int y, int button);

    private:

        void setupGUI();

        ofBaseApp* parent;
        tracker* _tracker;

        ofImage titleImg;

        gui GUI;
        guiButton playBut, createBut, configBut, exitBut;
};

#endif

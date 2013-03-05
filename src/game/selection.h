/*
 * select.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  The course select screen of the application.
 * Displays all courses in the /bin/courses and /bin/courses/user
 * directories.  Sets the course to be played based on the 
 * button that is pressed.
 *
 */

#pragma once
//#ifndef _SELECT_H
//#define _SELECT_H

#include "ofMain.h"
#include "tracker.h"
#include "gui.h"
#include "game.h"
#include "ofxFadable.h"

enum{PLAYING, SELECTING};

class selection : public ofBaseApp {

    public:

        selection();
        void setup(tracker* t, ofBaseApp* p);
        void update();
        void draw();
        void reset();

        void mousePressed(int x, int y, int button);

        string getCoursePath(int index);
        int getNumCourses();
        int* getCurrentCourse();
        void setMode(int newMode);
       
    private:

        void setupCourses();
        void setupGUI();

        ofBaseApp* parent;
        tracker* _tracker;
        game currentGame;
        ofxFadableRect fader;
        ofDirectory DIR;

        int numCourses, currentCourse, mode, nextMode;
        bool transition;
        vector<string> coursePaths;
        vector<string> courseNames;

        ofImage header;
        gui GUI;
        guiButton backBut;
        guiToggle contTog;
        vector<guiButton> courses;
};

//#endif

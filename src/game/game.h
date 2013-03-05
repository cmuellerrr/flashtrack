/*
 * game.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  Handles the gameplay of the application.
 * Draws the current course and tests the input to see 
 * if the course has been completed.
 *
 */

#ifndef _GAME_H
#define _GAME_H

#include "ofMain.h"
#include "ofTypes.h"
#include "tracker.h"
#include "gui.h"
#include "course.h"
#include "ofxFadable.h"

class game : public ofBaseApp {

    public:

        game();
        void setup(tracker* t, ofBaseApp* p);
        void update();
        void draw();
        void reset();

        void mousePressed(int x, int y, int button);

        bool* getContinuous();
        bool setCourseFromString(string course);
        void setNextCourse(string course);
    
    private:

        void setupGUI();
        bool courseComplete(int x, int y);
        bool outOfBounds();
        bool withinCircle(ofPoint position, ofPoint center, int radius);
        
        ofBaseApp* parent;
        tracker* _tracker;
        ofSoundPlayer completeSound;
        ofxFadableRect fader;

        bool drawing, transition, continuous;
        string nextCourse;

        course gameCourse;
        list<ofPoint> previousPoints;
        vector<edge> currentLine;

        ofImage edgeImg, nodeImg;

        gui GUI;
        guiButton backBut;        
};

#endif

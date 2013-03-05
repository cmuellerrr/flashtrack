/*
 * creator.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  The course creation screen of the application.
 * Allows a user to create courses of their own.  They can draw, 
 * move, and erase nodes and edges.  They can also load previous 
 * levels to edit.
 *
 */

#ifndef _CREATE_H
#define _CREATE_H

#include "ofMain.h"
#include "course.h"
#include "gui.h"
#include "tracker.h"
#include "XMLUtil.h"

#define SELECT_WIDTH 1
enum{DRAWING, MOVING, ERASING};

class creator : public ofBaseApp {

    public:

        creator();
        void setup(tracker* t, ofBaseApp* p);
        void update();
        void draw();
        void reset();

        void keyPressed(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        bool mousePressedGUI(int x, int y);
        void mouseReleased(int x, int y, int button);
        
    private:

        void setupGUI();
        void findCandidate(int x, int y);
        edge* findIntersectingEdge(int x, int y);
        bool containsEdge(vector<edge*> edges, edge* e);        

        ofBaseApp* parent;
        tracker* _tracker;
        XMLUtil xml;

        bool hasCandidate, hasIntersect;
        int mode;

        course currentCourse;
        ofPoint* candidate;
        ofPoint* selected;
        ofPoint* base;
        ofPoint temp, intersect;
        edge* intersectingEdge;

        ofImage header;

        gui GUI;
        guiOption drawOp, moveOp, eraseOp;
        guiOptionGroup createOptions;
        guiButton backBut, saveBut, loadBut, helpBut, clearBut;
        guiInputWindow saveWindow, loadWindow;
        guiHelpWindow helpWindow;
};

#endif

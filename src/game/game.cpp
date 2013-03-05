/*
 * game.cpp
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

#include "game.h"
#include "selection.h"
#include "math.h"
#include "XMLUtil.h"

/*
 * Default constructor.
 */
game::game() {
}

/*
 * Sets up the game application.  Sets tracker and parent.
 */
void game::setup(tracker* t, ofBaseApp* p) {
    _tracker = t;
    parent = p;
    drawing = false;
    continuous = true;
    transition = false;
    fader.setFadeSeconds(1.3f);
    fader.setUnitColor(0.0f, 0.0f, 0.0f);
    edgeImg.loadImage("images/edge_blue.png");
    nodeImg.loadImage("images/node_blue.png");

    completeSound.loadSound("sounds/ding.aif");
    completeSound.setVolume(0.25f);

    setupGUI();
}

/*
 * Sets up the game gui.
 */
void game::setupGUI() {
    backBut = guiButton("Back", TOP_BUT_POS_1, STD_BUT_W, STD_BUT_H, IMG_LOC_BACK);
    GUI.add(&backBut);
}

/*
 * Updates the game.  Checks for win/loss conditions.  Checks to see if the 
 * player has started drawing.  If so, adds the tracker's position to the 
 * current line.
 */
void game::update() {
    if (drawing) {
        previousPoints.push_back(ofPoint(_tracker->getX(), _tracker->getY()));
        if (!outOfBounds()) {    
            if (previousPoints.size() > 1) {
                list<ofPoint>::iterator it = previousPoints.end();
                it--;
                ofPoint* temp1 = &*it;
                it--;
                ofPoint* temp2 = &*it;
                currentLine.push_back(edge(temp1, temp2));
            }
            if (courseComplete(_tracker->getX(), _tracker->getY())) {
                completeSound.play();
                //mark as completed
                reset();
                int* courseNum = ((selection*)parent)->getCurrentCourse();
                int totalCourses = ((selection*)parent)->getNumCourses();
                if (continuous && *courseNum != totalCourses - 1) {
                    (*courseNum)++;
                    setNextCourse(((selection*)parent)->getCoursePath(*courseNum));
                }
                else {
                    ((selection*)parent)->setMode(SELECTING);
                }
            }
        }
        else {
            reset();
        }
    }
    else {
        if (withinCircle(ofPoint(_tracker->getX(), _tracker->getY()), gameCourse.start, IMP_NODE_SIZE)) drawing = true;
    }
    if (transition) {
        fader.updateFade();
        if (fader.getAlpha() > 0.9f && fader.isFadingIn()) {
            if (!setCourseFromString(nextCourse)) ((selection*)parent)->setMode(SELECTING);
            else {fader.fadeOut();}
        }
        if (fader.getAlpha() < 0.1f && fader.isFadingOut()) transition = false;
    }
}

/*
 * Draws the game application.  Draws the course, and if drawing, 
 * the current line.
 */
void game::draw() {
    ofPushStyle();
    gameCourse.draw();
    if (drawing) {
        for (int i = 0; i < currentLine.size(); i++) {
            currentLine[i].draw(&edgeImg);
            //ofSetRectMode(OF_RECTMODE_CENTER);
            //ofSetColor(255, 255, 255);
            //nodeImg.draw(currentLine[i].p1->x, currentLine[i].p1->y, 12, 12);
        }
    }
    GUI.draw();
    if (transition) {
        fader.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    ofPopStyle();
}

/*
 * Handles mouse presses.
 */
void game::mousePressed(int x, int y, int button) {
    if (backBut.checkHit(x, y)) {
        reset();
        ((selection*)parent)->setMode(SELECTING);
    }
}

/*
 * Sets the current course from a string specifying the course name.
 */
bool game::setCourseFromString(string courseName) {
    XMLUtil xml;
    return xml.loadCourse(courseName, &gameCourse);
}

/*
 * Sets the next course from a string specifying the course name.
 */
void game::setNextCourse(string course) {
    transition = true;
    nextCourse = course;
    fader.setAlpha(0);
    fader.fadeIn();
}

/*
 * Returns if the course has been completed. i.e. if the user is 
 * still drawing and they are in the finishing spot.
 */
bool game::courseComplete(int x, int y) {
    return drawing && withinCircle(ofPoint(x, y), gameCourse.finish, IMP_NODE_SIZE);
}

/*
 * Returns if the current line has intersected with any edge 
 * of the course.
 * TODO THIS IS INCOSISTENT.  DOES NOT ALWAYS CORRECTLY DETERMINE IF 
 * AN EDGE HAS BEEN CROSSED.
 */
bool game::outOfBounds() {
    if (currentLine.size() > 0) {
        for (list<edge>::iterator it = gameCourse.edges.begin(); it != gameCourse.edges.end(); it++) {
            if (currentLine.back().intersects(&*it)) return true;
        }
    }
    return false;
}

/*
 * Returns whether or not the point position is within the 
 * circle at point center with the given radius.
 */
bool game::withinCircle(ofPoint position, ofPoint center, int radius) {
    return pow((position.x - center.x), 2) + pow((position.y - center.y), 2) <= pow((double)radius, 2);
}

/*
 * Resets the game.
 */
void game::reset() {
    drawing = false;
    previousPoints.clear();
    currentLine.clear();
}

/*
 * Returns a pointer to the continuous flag variable.
 */
bool* game::getContinuous() {
    return &continuous;
}

/*
 * selection.cpp
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  The course selection screen of the application.
 * Displays all courses in the /bin/courses and /bin/courses/user
 * directories.  Sets the course to be played based on the 
 * button that is pressed.
 *
 */

#include "selection.h"
#include "screenManager.h"

const ofPoint togPos = ofPoint(100, 30);

/*
 * Default constructor.
 */
selection::selection() {
}

/*
 * Sets up the selectionion screen.  Sets the tracker and parent.
 */
void selection::setup(tracker* t, ofBaseApp* p) {
    _tracker = t;
    parent = p;
    currentGame.setup(t, this);
    mode = SELECTING;
    transition = false;
    fader.setFadeSeconds(1.3f);
    fader.setUnitColor(0.0f, 0.0f, 0.0f);

    header.loadImage(IMG_LOC_SELECT_H);

    setupCourses();
    setupGUI();
}

/*
 * Loads course names from /bin/courses and /bin/courses/user and 
 * stores their names and paths.  Also counts the total number. 
 */
void selection::setupCourses() {
    numCourses = DIR.listDir("courses/") - 1;
    for (int i = 0; i < numCourses; i++){
        coursePaths.push_back(DIR.getPath(i));
        courseNames.push_back(DIR.getName(i).substr(0, DIR.getName(i).length()-4));
    }
    int numUserCourses = DIR.listDir("courses/user");
    for (int i = 0; i < numUserCourses; i++){
        coursePaths.push_back(DIR.getPath(i));
        courseNames.push_back(DIR.getName(i).substr(0, DIR.getName(i).length()-4));
    }
    numCourses += numUserCourses;

    currentCourse = 0;
}

/*
 * Sets up the gui.  Makes a button for every course that was 
 * loaded.  Also tries to set a screen shot for each course.  
 * If one doesn't exist, the buttons just draws a square with 
 * the course name. 
 */
void selection::setupGUI() {
    backBut = guiButton("Back", TOP_BUT_POS_1, STD_BUT_W, STD_BUT_H, IMG_LOC_BACK);
    contTog = guiToggle("Continuous", togPos, STD_TOG_SIZE, STD_TOG_SIZE, currentGame.getContinuous());
    GUI.add(&backBut);
    GUI.add(&contTog);

    int yStep = 150;
    int xStep = (ofGetWidth() - 600) / 7;
    int xStart = xStep;
	int yStart = 100;
    xStep += 100;
    
    ofPoint coursePos = ofPoint(xStart,  yStart);
    for (int i = 0; i < numCourses; i++) {
        if (i != 0 && i % 6 == 0) {
            coursePos.y += yStep;
            coursePos.x = xStart;
        }
        courses.push_back(guiButton(courseNames[i], coursePos, STD_COURSE_W, STD_COURSE_H, "images/courses/course_" + ofToString(i + 1) + ".png"));
        coursePos.x += xStep;
    }
    for (int i = 0; i < numCourses; i++) {
        GUI.add(&courses[i]);
    }
}

/*
 * Updates the screen.  If playing, updates the game.
 */
void selection::update() {
    if (mode == PLAYING) {
        currentGame.update();
    }
    if (transition) {
        fader.updateFade();
        if (fader.getAlpha() > 0.9f && fader.isFadingIn()) {
            mode = nextMode;
            fader.fadeOut();
        }
        if (fader.getAlpha() < 0.1f && fader.isFadingOut()) transition = false;
    }
}

/*
 * Draws the screen.  If playing, draws the game.
 */
void selection::draw() {
    ofPushStyle();
    if (mode == PLAYING) {
        currentGame.draw();
    }
    else {
        ofSetColor(255, 255, 255);
        header.draw(ofGetWidth()/2-header.getWidth()/2, 0);    
        ofDrawBitmapString("Continuous Play", togPos.x + 50, togPos.y + 20);
        GUI.draw();
    }
    if (transition) {
        fader.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    ofPopStyle();
}


/*
 * Handles mouse presses.  If playing, passes input to the game.
 * Sets the game's course if a course button is pressed.
 */
void selection::mousePressed(int x, int y, int button) {
    if (mode == PLAYING) {
        currentGame.mousePressed(x, y, button);
    }
    else {
        if (backBut.checkHit(x, y)) {
            ((screenManager*)parent)->setMode(TITLE);
        }
        for (int i = 0; i < numCourses; i++) {
            if (courses[i].checkHit(x, y)) {
                if (currentGame.setCourseFromString(coursePaths[i])) {
                    setMode(PLAYING);
                    currentCourse = i;
                }
            }
        }
        contTog.mousePressed(x, y);
    }
}

/*
 * Sets the current mode of the screen.  Can be either SELECTING
 * or PLAYING.
 */
void selection::setMode(int newMode) {
    nextMode = newMode;
    transition = true;
    fader.setAlpha(0);
    fader.fadeIn();
}

/*
 * gets the path of the current course.
 */
string selection::getCoursePath(int index) {
    if (index >= 0 && index < numCourses) return coursePaths[index];
    return "";
}

/*
 * Gets the number of courses.
 */
int selection::getNumCourses() {
    return numCourses;
}

/*
 * Gets a pointer to the value of currentCourse.
 * currentCourse represents the index of the course currently 
 * being played.
 */
int* selection::getCurrentCourse() {
    return &currentCourse;
}

/*
 * Resests the selectionion screen. 
 */
void selection::reset() {
    coursePaths.clear();
    courseNames.clear();
    courses.clear();
    setupCourses();
    setupGUI();
}

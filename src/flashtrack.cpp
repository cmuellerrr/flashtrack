/*
 * flashtrack.cpp
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  Sets up the tracker and gives control
 * over to the screen manager.
 *
 */

#include "flashtrack.h"

/*
 * Default constructor.
 */
flashtrack::flashtrack() {
}

/*
 * Sets up the flashtrack object.
 */
void flashtrack::setup() {
    _tracker.setup(320, 240, ofGetWidth(), ofGetHeight());
    manager.setup(&_tracker);
    ofBackground(0, 0, 0);
    bgMusic.loadSound("sounds/Aurora.mp3");
    bgMusic.setLoop(true);
    bgMusic.play();
}

/*
 * Updates the tracker and screen manager.
 */
void flashtrack::update() {
    _tracker.update();
    manager.update();
}

/*
 * Draws the tracker and the screen manager.
 */
void flashtrack::draw() {
    _tracker.draw();
    manager.draw();
}

/*
 * Handles key presses.  Sends input to screen manager.
 */
void flashtrack::keyPressed(int key) {
    manager.keyPressed(key);
}

/*
 * Handles key releases.  Sends input to screen manager.
 */
void flashtrack::keyReleased(int key) {
    manager.keyReleased(key);
}

/*
 * Handles mouse movement.  Sends input to screen manager.
 */
void flashtrack::mouseMoved(int x, int y) {
    manager.mouseMoved(x, y);
}

/*
 * Handles mouse drags.  Sends input to screen manager.
 */
void flashtrack::mouseDragged(int x, int y, int button) {
    manager.mouseDragged(x, y, button);
}

/*
 * Handles mouse presses.  Sends input to screen manager.
 */
void flashtrack::mousePressed(int x, int y, int button) {
    manager.mousePressed(x, y, button);
}

/*
 * Handles mouse releases.  Sends input to screen manager.
 */
void flashtrack::mouseReleased(int x, int y, int button) {
    manager.mouseReleased(x, y, button);
}

/*
 * Handles when the screen is resized.  Passes info to screen 
 * manager.
 */
void flashtrack::resized(int w, int h) {
    _tracker.resized(w, h);
}

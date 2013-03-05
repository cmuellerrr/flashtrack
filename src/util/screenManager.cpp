/*
 * screenManager.cpp
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

#include "screenManager.h"
#include "XMLUtil.h"

/*
 * Default constructor.
 */
screenManager::screenManager() {
    
}

/*
 * Sets up the screen manager.  Sets the tracker.
 */
void screenManager::setup(tracker* t) {
    _tracker = t;

    XMLUtil xml;
    xml.loadSettings(_tracker);

    titleApp.setup(_tracker, this);
    selectApp.setup(_tracker, this);
    createApp.setup(_tracker, this);
    configApp.setup(_tracker, this);

    mode = TITLE;
    fader.setFadeSeconds(1.3f);
    fader.setUnitColor(0.0f, 0.0f, 0.0f);
    transition = true;
    fader.setAlpha(1);
    fader.fadeOut();
}

/*
 * Updates the active application.
 */
void screenManager::update() {    
    switch (mode) {
        case TITLE:
            titleApp.update();
            break;
        case SELECT:
            selectApp.update();
            break;
        case CREATE:
            createApp.update();
            break;
        case CONFIG:
            configApp.update();
            break;
    }
    if (transition) {
        fader.updateFade();
        if (fader.getAlpha() > 0.9f && fader.isFadingIn()) {
            if (nextMode == CREATE) createApp.reset();
            if (nextMode == SELECT) selectApp.reset();
            mode = nextMode;
            fader.fadeOut();
        }
        if (fader.getAlpha() < 0.1f && fader.isFadingOut()) transition = false;
    }
}

/*
 * Draws the active application.
 */
void screenManager::draw() {
    ofPushStyle();
    switch (mode) {
        case TITLE:
            titleApp.draw();
            break;
        case SELECT:
            selectApp.draw();
            break;
        case CREATE:
            createApp.draw();
            break;
        case CONFIG:
            configApp.draw();
            break;
    }
    if (transition) {
        ofSetRectMode(OF_RECTMODE_CORNER);
        fader.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    ofPopStyle();
}

/*
 * Passes key presses to the active application.
 */
void screenManager::keyPressed  (int key) {    
    if (!transition) {
        switch (mode) {
            case TITLE:
                //titleApp.keyPressed(key);
                break;
            case SELECT:
                //selectApp.keyPressed(key);
                break;
            case CREATE:
                createApp.keyPressed(key);
                break;
            case CONFIG:
                //configApp.keyPressed(key);
                break;
        }
    }
}

/*
 * Passes key releases to the active application.
 */
void screenManager::keyReleased(int key) {
    if (!transition) {
        switch (mode) {
            case TITLE:
                //titleApp.keyReleased(key);
                break;
            case SELECT:
                //selectApp.keyReleased(key);
                break;
            case CREATE:
                //createApp.keyReleased(key);
                break;
            case CONFIG:
                //configApp.keyReleased(key);
                break;
        }
    }
}

/*
 * Passes mouse movement to the active application.
 */
void screenManager::mouseMoved(int x, int y ) {
    if (!transition) {
        switch (mode) {
            case TITLE:
                //titleApp.mouseMoved(x, y);
                break;
            case SELECT:
                //selectApp.mouseMoved(x, y);
                break;
            case CREATE:
                createApp.mouseMoved(x, y);
                break;
            case CONFIG:
                //configApp.mouseMoved(x, y);
                break;
        }
    }
}

/*
 * Passes mouse drags to the active application.
 */
void screenManager::mouseDragged(int x, int y, int button) {
    if (!transition) {
        switch (mode) {
            case TITLE:
                //titleApp.mouseDragged(x, y, button);
                break;
            case SELECT:
                //selectApp.mouseDragged(x, y, button);
                break;
            case CREATE:
                createApp.mouseDragged(x, y, button);
                break;
            case CONFIG:
                configApp.mouseDragged(x, y, button);
                break;
        }
    }

}

/*
 * Passes mouse presses to the active application.
 */
void screenManager::mousePressed(int x, int y, int button) {
    if (!transition) {
        switch (mode) {
            case TITLE:
                titleApp.mousePressed(x, y, button);
                break;
            case SELECT:
                selectApp.mousePressed(x, y, button);
                break;
            case CREATE:
                createApp.mousePressed(x, y, button);
                break;
            case CONFIG:
                configApp.mousePressed(x, y, button);
                break;
        }
    }
}

/*
 * Passes mouse releases to the active application.
 */
void screenManager::mouseReleased(int x, int y, int button) {
    if (!transition) {
        switch (mode) {
            case TITLE:
                //titleApp.mouseReleased(x, y, button);
                break;
            case SELECT:
                //selectApp.mouseReleased(x, y, button);
                break;
            case CREATE:
                createApp.mouseReleased(x, y, button);
                break;
            case CONFIG:
                //configApp.mouseReleased(x, y, button);
                break;
        }
    }
}

/*
 * Sets the active application.
 */
void screenManager::setMode(int newMode) {
    nextMode = newMode;
    transition = true;
    fader.setAlpha(0);
    fader.fadeIn();
}

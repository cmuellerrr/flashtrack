/*
 * title.cpp
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  The title screen of the application.
 *
 */

#include "title.h"
#include "screenManager.h"

/*
 * Default constructor
 */
title::title() {
}

/*
 * Sets up the title screen.  Sets tracker and parent.
 */
void title::setup(tracker* t, ofBaseApp* p) {
    _tracker = t;
    parent = p;
    titleImg.loadImage(IMG_LOC_LOGO);
    setupGUI();
}

/*
 * Sets up the title screen gui.
 */
void title::setupGUI() {
    const int buttonX = ofGetWidth()/2 - TITLE_BUT_W/2;

    playBut = guiButton("Play", ofPoint(buttonX, 400), TITLE_BUT_W, TITLE_BUT_H, IMG_LOC_PLAY);
    createBut = guiButton("Create", ofPoint(buttonX, 450), TITLE_BUT_W, TITLE_BUT_H, IMG_LOC_CREATE);
    configBut = guiButton("Configure", ofPoint(buttonX, 500), TITLE_BUT_W, TITLE_BUT_H, IMG_LOC_CONFIG);
    exitBut = guiButton("Exit", ofPoint(buttonX, 550), TITLE_BUT_W, TITLE_BUT_H, IMG_LOC_EXIT);
    GUI.add(&playBut);
    GUI.add(&createBut);
    GUI.add(&configBut);
    GUI.add(&exitBut);
}

/*
 * Draws the title screen.
 */
void title::draw() {
    ofPushStyle();

    ofSetColor(255, 255, 255);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetLineWidth(SELECT_WIDTH);

    titleImg.draw(ofGetWidth()/2, ofGetHeight()/2);
    GUI.draw();

    ofPopStyle();
}

/*
 * Updates the title screen.
 * TODO may not need a tracker at all.
 */
void title::update() {
    _tracker->update();
}

/*
 * Handles mouse presses.  Sets the active application if 
 * the a gui button is pressed.
 */
void title::mousePressed(int x, int y, int button) {
    if (playBut.checkHit(x, y)) {
        ((screenManager*)parent)->setMode(SELECT);
    }
    if (createBut.checkHit(x, y)) {
        ((screenManager*)parent)->setMode(CREATE);
    }
    if (configBut.checkHit(x, y)) {
        ((screenManager*)parent)->setMode(CONFIG);
    }
    if (exitBut.checkHit(x, y)) {
        OF_EXIT_APP(1);
    }
}

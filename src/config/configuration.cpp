/*
 * configuration.cpp
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  The configurationuration screen of the application.
 * Configures the application to track either a determined color 
 * or threshold.
 *
 */

#include "configuration.h"
#include "screenManager.h"

/*
 * Default constructor.
 */
configuration::configuration() {
 
}

/*
 * Deletion of class. 
 */
configuration::~configuration() {

}

/*
 * Sets up the configuration screen.  Sets the tracker and 
 * parent.
 */
void configuration::setup(tracker* t, ofBaseApp* p) {
    _tracker = t;
    parent = p;

    header.loadImage(IMG_LOC_CONFIG_H);
    setupGUI();
}

/*
 * Sets up the gui.  Separates the gui elements when in light mode 
 * and manual mode for easy drawing/dealing with input.
 */
void configuration::setupGUI() {
    thresholdSlider = guiSlider("Threshold", _tracker->getThreshold(), ofPoint(20, 360), STD_SLIDER_W, STD_SLIDER_H, 0, 255);
    lightGUI.add(&thresholdSlider);

    hueSlider = guiSlider("Hue Range", _tracker->getHueRange(), ofPoint(20, 330), STD_SLIDER_W, STD_SLIDER_H, 0, 255);
    saturationSlider = guiSlider("Saturation Range", _tracker->getSaturationRange(), ofPoint(20, 360), STD_SLIDER_W, STD_SLIDER_H, 0, 255);
    valueSlider = guiSlider("Value Range", _tracker->getValueRange(), ofPoint(20, 390), STD_SLIDER_W, STD_SLIDER_H, 0, 255);
    manualGUI.add(&hueSlider);
    manualGUI.add(&saturationSlider);
    manualGUI.add(&valueSlider);

    backBut = guiButton("Back", TOP_BUT_POS_1, STD_BUT_W, STD_BUT_H, IMG_LOC_BACK);
    saveBut = guiButton("Save", TOP_BUT_POS_2, STD_BUT_W, STD_BUT_H, IMG_LOC_SAVE);
    helpBut = guiButton("Help", TOP_BUT_POS_3, STD_BUT_W, STD_BUT_H, IMG_LOC_HELP);
    GUI.add(&backBut);
    GUI.add(&saveBut);
    GUI.add(&helpBut);

    int togY = ofGetHeight()-STD_TOG_SIZE-20;

    lightOp = guiOption("Light", ofPoint(20, togY), STD_TOG_SIZE, STD_TOG_SIZE, LIGHT);
    lightOp.setLable(true);
    manualOp = guiOption("Manual", ofPoint(140, togY), STD_TOG_SIZE, STD_TOG_SIZE, MANUAL);
    manualOp.setLable(true);
    if (_tracker->mode == LIGHT) lightOp.setActive(true);
    else { manualOp.setActive(true);}
    trackOptions.setValue(&_tracker->mode);
    trackOptions.add(&lightOp);
    trackOptions.add(&manualOp);
    GUI.add(&trackOptions);

    helpWindow = guiHelpWindow(IMG_LOC_HELP_CONFIG);
    GUI.add(&helpWindow);
}

/*
 * Updates the configuration screen. 
 */
void configuration::update() {
}

/*
 * Draws the configuration screen.  Depending on what mode it is 
 * in, it draws a different top video feed and sliders. 
 */
void configuration::draw() {
    ofPushStyle();
    header.draw(ofGetWidth()/2-header.getWidth()/2, 0);

    if (_tracker->mode == LIGHT) _tracker->getGrayscaleData()->draw(20, 50);
    else {_tracker->getColorData()->draw(20, 50);}
    _tracker->getContours()->draw(20, 50);
    ofSetColor(255, 255, 255);
    _tracker->getThresholdData()->draw(20, 420);

    if (_tracker->mode == LIGHT) lightGUI.draw();
    else {manualGUI.draw();}
    GUI.draw();
    ofPopStyle();
}

/*
 * Handles when the mouse is dragged.  Checks the sliders, 
 * depending on the current mode. 
 */
void configuration::mouseDragged(int x, int y, int button) {
    if (_tracker->mode == LIGHT) lightGUI.mouseDragged(x, y);
    else {manualGUI.mouseDragged(x, y);}
}

/*
 * Handles when the mouse is pressed.
 */
void configuration::mousePressed(int x, int y, int button) {
    GUI.mousePressed(x, y);
    if (_tracker->mode == LIGHT) lightGUI.mousePressed(x, y);
    else {manualGUI.mousePressed(x, y);}

    if (backBut.checkHit(x, y)) {
        ((screenManager*)parent)->setMode(TITLE);
    }
    if (saveBut.checkHit(x, y)) {
        xml.saveSettings(_tracker);
    }
    if (helpBut.checkHit(x, y)) {
        helpWindow.show();
    }
    //MAGIC NUMBERS!!
    if (_tracker->mode == MANUAL && x >= 20 && x <= 340 && y >= 50 && y <= 290) {    
        _tracker->setHueSatValByPixel((y-50) * 320 + (x-20));
    }
}

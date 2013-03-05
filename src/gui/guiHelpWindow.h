/*
 * guiHelpWindow.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  A help window.  Just draws a given image 
 * and an "ok" button.
 *
 */

#ifndef _GUI_HELP_WINDOW_H
#define _GUI_HELP_WINDOW_H

#include "ofTypes.h"
#include "guiButton.h"

class guiHelpWindow {

    public:

        /**
         * Default constructor.
         */
        guiHelpWindow() {
            width = 0;
            height = 0;
            active = false;
            ok = guiButton();
            windowPos = ofPoint(0);
            imagePos = ofPoint(0);
        }

        /**
         * Constructor taking in description, position, size, and a function to be 
         * preformed when the "OK" button is pressed.
         */
        guiHelpWindow(string _image) {
            image.loadImage(_image);
            width = image.getWidth() + 20;
            height = image.getHeight() + 50;
            windowPos = ofPoint(ofGetWidth()/2 - width/2, ofGetHeight()/2 - height/2);
            imagePos = ofPoint(windowPos.x + 10, windowPos.y + 10);
            active = false;
            ok = guiButton("OK", ofPoint(imagePos.x + image.getWidth() - 60, imagePos.y + image.getHeight() + 5), 60, 30, "images/buttons/ok.png");
        }

        /**
         * Handles when the mouse button is pressed.
         */
        bool mousePressed(int x, int y) {
            if (active) {
                if (ok.checkHit(x, y)) {
                    hide();
                    return true;
                }
                return checkHit(x, y);
            }
            return false;
        }

        /**
         * Draws the window if set to active.
         */
        void draw() {
            ofPushStyle();
            if (active) {
                ofFill();
                ofSetRectMode(OF_RECTMODE_CORNER);
                ofSetColor(100, 100, 100);
                ofRect(windowPos.x, windowPos.y, width, height);
                ofSetColor(255, 255, 255);
                image.draw(imagePos.x, imagePos.y);
                ok.draw();
            }
            ofPopStyle();
        }

        /**
         * Sets the window to active.
         */
        void show() {
            active = true;
        }

        /**
         * Deactivates the window.
         */
        void hide() {
            active = false;
        }


        bool checkHit(int x, int y) {
            return (x >= windowPos.x && x <= windowPos.x + width &&
                y >= windowPos.y && y <= windowPos.y + height);
        }

        bool checkOK(int x, int y) {
            return active && ok.mousePressed(x, y);
        }

    private:

        int width, height;
        bool active;
        guiButton ok;
        ofImage image;
        ofPoint windowPos, imagePos;
};

#endif

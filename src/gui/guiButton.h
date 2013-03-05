/*
 * guiButton.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  A button object.  Can either hold 
 * an image or automatically draws a square with its 
 * name.  Can take in a pointer to a void function 
 * to be called when pressed.
 *
 */

#ifndef _GUI_BUTTON_H
#define _GUI_BUTTON_H

#include "ofTypes.h"

typedef void (*voidFunction)();

class guiButton {

    public:

        /**
         * Default constructor.
         */
        guiButton() {
            position = ofPoint(0);
            width = 0;
            height = 0;
            hitFunc = 0;
            hasImage = false;
        }

        /**
         * Constructor setting the name, position, width, and height.  Adds an optional
         * function.
         */
        guiButton(string _name, ofPoint pos, int w, int h, string _image = "", voidFunction f = 0) {
            name = _name;
            position = pos;
            width = w;
            height = h;
            hitFunc = f;
            hasImage = false;
            if (_image != "") {
                hasImage = image.loadImage(_image);
                if (hasImage) image.resize(w, h);
            }
        }

        /**
         * Calls the hit function if the given (x, y) lies within the 
         * button.
         */
        bool mousePressed(int x, int y) {
            if (checkHit(x, y)) {
                if (hitFunc != 0) hitFunc();
                return true;
            }
            return false;
        }

        /**
         * Determines if the given position is within the bounds of the button.
         */
        bool checkHit(int x, int y) {
            return (x >= position.x && x <= position.x + width &&
                y >= position.y && y <= position.y + height);
        }

        /**
         * Draws the button.
         */
        void draw() {
            ofPushStyle();
            ofSetColor(255, 255, 255);
            if (hasImage) image.draw(position.x, position.y);
            else {
                ofSetColor(220, 220, 220);
                ofRect(position.x, position.y, width, height);
                ofSetColor(0, 0, 0);
                ofDrawBitmapString(name, position.x, position.y + 12);
            }
            ofPopStyle();
        }

        /**
         * Sets the button's hit function.
         */
        void setHitFunc(voidFunction f) {
            hitFunc = f;
        }

        /**
         * Sets the button's image to that specified by the 
         * given url.
         */
        void setImage(string _image) {
            if (image.loadImage(_image)) {
                image.resize(width, height);
                hasImage = true;
            }
        }

    private:

        string name;
        ofPoint position;
        int width, height;    
        bool hasImage;
        ofImage image;
        voidFunction hitFunc;
};

#endif

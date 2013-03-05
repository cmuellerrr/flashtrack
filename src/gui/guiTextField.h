/*
 * guiTextField.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  A text field.  Registers button presses
 * and adds them to the string value.  Must be selected 
 * for the presses to register.
 *
 */

#ifndef _GUI_TEXT_FIELD_H
#define _GUI_TEXT_FIELD_H

#include "ofTypes.h"

class guiTextField {
    public:

        /**
         * Default constructor.
         */
        guiTextField() {
            position = ofPoint(0);
            width = 0;
            height = 0;
            edit = false;
        }

        /**
         * Constructor taking in position and size.
         */
        guiTextField(ofPoint pos, int w, int h) {
            position = pos;
            width = w;
            height = h;
            edit = false;
        }

        /**
         * Handles mouse presses.
         */
        bool mousePressed(int x, int y) {
            if (checkHit(x, y)) edit = true;
            else {edit = false;}
            return edit;
        }

        /**
         * Checks to see if the given mouse position is within the
         * bounds of the text field.
         */
        bool checkHit(int x, int y) {
            return (x >= position.x && x <= position.x + width &&
                y >= position.y && y <= position.y + height);
        }

        /**
         * Handles key presses.
         */
        void keyPressed(int key) {
            if (edit) {
                if (key == OF_KEY_BACKSPACE && text.size() > 0) {
                    text.erase(text.size() - 1);
                }
                else {
                    text += key;
                }
            }
        }

        /**
         * Draws the text field.
         */
        void draw() {
            ofSetColor(220, 220, 220);
            ofRect(position.x, position.y, width, height);
            ofSetColor(0, 0, 0);
            ofDrawBitmapString(text, position.x, position.y + 12);
            if (edit) {
                ofNoFill();
                ofSetColor(255, 255, 255);
                ofRect(position.x, position.y, width+1, height+1);
            }
            ofFill();
        }

        /**
         * Gets the string contained in the text field.
         */
        string getText() {
            return text;
        }

        /**
         * Clears the text field.
         */
        void clear() {
            text.clear();
        }

    private:

        string text;
        ofPoint position;
        int width, height;
        bool edit;
};

#endif

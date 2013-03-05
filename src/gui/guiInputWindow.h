/*
 * guiInputWindow.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  An input window for entering text.  
 * Renders a description, text field, and "ok" and 
 * "cancel" buttons.  Can also take a string function 
 * to be called when "ok" is pressed.
 *
 */

#ifndef _GUI_INPUT_WINDOW_H
#define _GUI_INPUT_WINDOW_H

#include "ofTypes.h"
#include "guiButton.h"
#include "guiTextField.h"

typedef void (*stringFunction)(string);

class guiInputWindow {

    public:

        /**
         * Default constructor.
         */
        guiInputWindow() {
            position = ofPoint(0);
            width = 0;
            height = 0;
            active = false;
            okFunc = 0;
            ok = guiButton();
            cancel = guiButton();
            field = guiTextField();
        }

        /**
         * Constructor taking in description, position, size, and a function to be 
         * preformed when the "OK" button is pressed.
         */
        guiInputWindow(string _text, stringFunction f = 0) {
            text = _text;
            width = 400;
            height = 150;
            position = ofPoint(ofGetWidth()/2 - width/2, ofGetHeight()/2 - height/2);
            active = false;
            okFunc = f;
            ok = guiButton("OK", ofPoint(position.x + width - 70, position.y + height - 40), 60, 30, "images/buttons/ok.png");
            cancel = guiButton("Cancel", ofPoint(position.x + 10, position.y + height - 40), 60, 30, "images/buttons/cancel.png");
            field = guiTextField(ofPoint(position.x + 10, position.y + 50), width - 20, 20);
        }

        /**
         * Handles when the mouse button is pressed.
         */
        bool mousePressed(int x, int y) {
            if (active) {
                if (field.mousePressed(x, y)) return true;
                if (ok.checkHit(x, y)) {
                    //if (okFunc != 0) okFunc(field.getText());
                    //hide();
                    return true;
                }
                if (cancel.checkHit(x, y)) {
                    hide();
                    return true;
                }
                return checkHit(x, y);
            }
            return false;
        }

        /**
         * Handles key presses for entering text.
         */
        void keyPressed(int key) {
            if (active) field.keyPressed(key);
        }

        /**
         * Draws the window if set to active.
         */
        void draw() {
            if (active) {
                ofPushStyle();
                ofFill();
                ofSetColor(100, 100, 100);
                ofRect(position.x, position.y, width, height);
                ofSetColor(255, 255, 255);
                ofDrawBitmapString(text, position.x + 10, position.y + 20);
                ok.draw();
                cancel.draw();
                field.draw();
                ofPopStyle();
            }
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
            field.clear();
            active = false;
        }

        /**
         * Sets the window's "OK" function to f.
         */
        void setOkFunc(stringFunction f) {
            okFunc = f;
        }

        bool checkHit(int x, int y) {
            return (x >= position.x && x <= position.x + width &&
                y >= position.y && y <= position.y + height);
        }

        bool checkOK(int x, int y) {
            return active && ok.mousePressed(x, y);
        }

        bool checkCancel(int x, int y) {
            return active && cancel.mousePressed(x, y);
        }

        guiTextField* getField() {
            return &field;
        }

    private:

        string text;
        ofPoint position;
        int width, height;
        bool active;
        stringFunction okFunc;
        guiButton ok, cancel;
        guiTextField field;
};

#endif

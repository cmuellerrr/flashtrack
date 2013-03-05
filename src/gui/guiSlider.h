/*
 * guiSlider.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  A slider object.  Sets the value of 
 * a given pointer to that of the slider.
 *
 */

#ifndef _GUI_SLIDER_H
#define _GUI_SLIDER_H

#include "ofTypes.h"

class guiSlider {

    public:
        
        /**
         * Default constructor.
         */
        guiSlider() {
            position = ofPoint(0);
            width = 0;
            height = 0;
            minVal = 0;
            maxVal = 1;
            edit = false;
            filled = 0;
        }

        /**
         * Constructor that sets the necessary attributes for this slider.
         */
        guiSlider(string _name, int* _value, ofPoint pos, int w, int h, double low, double high) {
            name = _name;
            value = _value;
            position = pos;
            width = w;
            height = h;
            minVal = low;
            maxVal = high;
            edit = false;
            updatePercent();
        }

        /**
         * Draws the slider.
         */
        void draw() {
            ofSetColor(220, 220, 220);
            ofFill();
            ofRect(position.x, position.y, width, height);
            ofSetColor(0, 0, 255);
            ofRect(position.x, position.y, filled * width, height);
            ofSetColor(255, 255, 255);
            ofDrawBitmapString(name, position.x, position.y - 5);
            char reportStr[1024];
            sprintf(reportStr, "%i", *value);
            ofDrawBitmapString(reportStr, position.x + width - 25, position.y - 5);
        }

        /**
         * Handles mouse presses.
         * Updates value based on the mouse position.
         */
        bool mousePressed(int x, int y) {
            edit = checkHit(x, y);
            if (edit) updateValue(x);
            return edit;
        }

        /**
         * Handles when the mouse is dragged.  
         * Updates value based on the mouse position.
         */
        bool mouseDragged(int x, int y) {
            if (edit) updateValue(x);
            return edit;
        }

        /**
         * Checks to see if the mouse position is within the boundaries 
         * of the slider.
         */
        bool checkHit(int x, int y) {
            return (x >= position.x && x <= position.x + width &&
                y >= position.y && y <= position.y + height);
        }

    private:

        /**
         * Updates the amount of slider to be filled based on 
         * value's.....value.
         */
        void updatePercent() {
            filled = (*value - minVal) / (maxVal - minVal);
        }

        /**
         * Updates value based on the given x position of the mouse.
         */
        void updateValue(int x) {
            *value = ofClamp((maxVal - minVal) * ((x - position.x) / width), minVal, maxVal);
            updatePercent();
        }

        string name;
        ofPoint position;
        int width, height;
        bool edit;
        int* value;
        double minVal, maxVal, filled;
};

#endif

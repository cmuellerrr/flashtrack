/*
 * guiOption.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  An option object.  Represents a value 
 * that will be set when the option is selected.
 *
 */

#ifndef _GUI_OPTION_H
#define _GUI_OPTION_H

#include "ofTypes.h"

class guiOption {

    public:

        guiOption() {
            position = ofPoint(0);
            width = 0;
            height = 0;
            value = 0;
            hasImage = false;
            active = false;
            showLable = false;
        }

        guiOption(string _name, ofPoint pos, int w, int h, int _value, string _image = "") {
            name = _name;
            position = pos;
            width = w;
            height = h;
            value = _value;
            if (_image != "") {
                hasImage = image.loadImage(_image);
                if (hasImage) image.resize(w, h);
            }
            active = false;
            showLable = false;
        }

        void draw() {
            ofPushStyle();
            if (active == true) ofSetColor(255, 255, 255);
            else {ofSetColor(220, 220, 220);}
            ofFill();
            ofRect(position.x, position.y, width, height);
            if (hasImage) image.draw(position.x, position.y);
            ofSetColor(255, 255, 255);
            if (showLable) ofDrawBitmapString(name, position.x + width + 10, position.y + height/2);
            ofPopStyle();
        }

        bool mousePressed(int x, int y) {
            if (checkHit(x, y)) {
                active = true;
                return true;
            }
            return false;
        }

        bool checkHit(int x, int y) {
            return (x >= position.x && x <= position.x + width &&
                y >= position.y && y <= position.y + height);
        }

        bool isActive() {
            return active;
        }

        void setActive(bool set) {
            active = set;
        }

        int getValue() {
            return value;
        }

        void setLable(bool set) {
            showLable = set;
        }

    private:

        string name;
        ofPoint position;
        int width, height, value;
        bool active, hasImage, showLable;
        ofImage image;

};

#endif

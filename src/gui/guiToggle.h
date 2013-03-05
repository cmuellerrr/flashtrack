#ifndef _GUI_TOGGLE
#define _GUI_TOGGLE

#include "ofTypes.h"

/**
 * A custom gui class for representing toggle buttons (i.e. radio buttons).
 */
class guiToggle {
	public:

		/**
		 * Default constructor.
		 */
		guiToggle() {
            position = ofPoint(0);
			width = 0;
			height = 0;
			value = false;
			hasImage = false;
			showLable = false;
		}

		/**
		 * Constructor setting the name, position, size, value, and an optional image url.
		 */
		guiToggle(string _name, ofPoint pos, int w, int h, bool* _value, string _image = "") {
			name = _name;
			position = pos;
			width = w;
			height = h;
			value = _value;
			if (_image != "") {
    			hasImage = image.loadImage(_image);
	    		if (hasImage) image.resize(w, h);
			}
			showLable = false;
		}

		/**
		 * Handles mouse presses.  Not used if part of a toggle group.
		 * This is because the group must keep toggles mutually exclusive 
		 * and require one toggle to be set to true.
		 */
		bool mousePressed(int x, int y) {
			if (checkHit(x, y)) { 
				onHit();
				return true;
			}
			return false;
		}

		/**
		 * Switches value to true/false.
		 */
		void onHit() {
            *value = !*value;
		}

		/**
		 * Checks if the given mouse position is within the bounds of 
		 * the toggle.
		 */
		bool checkHit(int x, int y) {
            return (x >= position.x && x <= position.x + width &&
				y >= position.y && y <= position.y + height);
		}

		/**
		 * Draws the toggle.
		 */
		void draw() {
			ofPushStyle();
			if (*value == true) ofSetColor(255, 255, 255);
			else {ofSetColor(220, 220, 220);}

			ofRect(position.x, position.y, width, height);
			if (hasImage) image.draw(position.x, position.y);

			ofSetColor(255, 255, 255);
			if (showLable) ofDrawBitmapString(name, position.x + width + 10, position.y + height/2);
			ofPopStyle();
		}

		/**
		 * Sets value to false.
		 */
		void toggleOff() { 
            *value = false;
		}

		/**
		 * Sets value to true.
		 */
		void toggleOn() { 
            *value = true;
		}

		/**
		 * Sets the toggle's image to that specified by the 
		 * given url.
		 */
		void setImage(string _image) {
			if (image.loadImage(_image)) {
			    image.resize(width, height);
			    hasImage = true;
			}
		}

		/**
		 * Returns value.
		 */
		bool getValue() {
            return *value;
		}
		
		void setLable(bool set) {
			showLable = set;
		}

	private:

		string name;
		ofPoint position;
		int width, height;
        bool* value;
		bool hasImage, showLable;
		ofImage image;
};

#endif
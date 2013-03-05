#ifndef _GUI_TOGGLE_GROUP
#define _GUI_TOGGLE_GROUP

#include "guiToggle.h"

/**
 * A custom gui class for representing a toggle group (i.e. a group of radio buttons).  
 * All toggles are mutually exclusive and one toggle must be set to true at all times.
 */
class guiToggleGroup {
	public:

		/**
		 * Default constructor.
		 */
		guiToggleGroup() {}

		/**
		 * Handles mouse presses.  Modifies the hit toggle and turns all other toggles 
		 * off if one is hit.
		 */
		bool mousePressed(int x, int y) {
			for (list<guiToggle*>::iterator it = toggles.begin(); it != toggles.end(); it++) {
				if ((**it).checkHit(x, y)) {
					if ((**it).getValue() == false) {
                        (**it).onHit();
					    for (list<guiToggle*>::iterator er = toggles.begin(); er != toggles.end(); er++) {
                            if (er != it) (**er).toggleOff();
					    }
					}
					return true;
				}
			}
			return false;
		}

		/**
		 * Draws each toggle individually.
		 */
		void draw() {
			for (list<guiToggle*>::iterator it = toggles.begin(); it != toggles.end(); it++) {
                (**it).draw();
			}
		}

		/**
		 * Adds a toggle to the group.
		 */
		void addToggle(guiToggle* t) {
            toggles.push_back(t);
		}

    private:
	
		list<guiToggle*> toggles;
};

#endif
/*
 * guiOptionGroup.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  A group of option buttons.  Contains a 
 * pointer to a value that will be set based on the active
 * option.
 *
 */

#ifndef _GUI_OPTION_GROUP_H
#define _GUI_OPTION_GROUP_H

#include "guiOption.h"

class guiOptionGroup {
    
    public:

        guiOptionGroup() {}

        void draw() {
            for (list<guiOption*>::iterator it = options.begin(); it != options.end(); it++) {
                (**it).draw();
            }
        }

        bool mousePressed(int x, int y) {
            for (list<guiOption*>::iterator it = options.begin(); it != options.end(); it++) {
                if ((**it).checkHit(x, y)) {
                    if (!(**it).isActive()) {
                        (**it).setActive(true);
                        *value = (**it).getValue();
                        for (list<guiOption*>::iterator er = options.begin(); er != options.end(); er++) {
                           if (er != it) (**er).setActive(false);
                        }
                    }
                    return true;
                }
            }
            return false;
        }

        void add(guiOption* o) {
            options.push_back(o);
        }

        void setValue(int* _value) {
            value = _value;
        }

    private:

        list<guiOption*> options;
        int* value;
};

#endif

/*
 * gui.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  A gui object.  Holds all gui elements and 
 * allows them to be accessed as one.  Calls all individual 
 * elements' methods.
 *
 */

#ifndef _GUI_H
#define _GUI_H

#include "guiButton.h"
#include "guiToggle.h"
#include "guiSlider.h"
#include "guiTextField.h"
#include "guiInputWindow.h"
#include "guiOption.h"
#include "guiOptionGroup.h"
#include "guiHelpWindow.h"

//Define standard gui sizes
#define STD_BUT_W 60
#define STD_BUT_H 30
#define STD_TOG_SIZE 30
#define TITLE_BUT_W 100
#define TITLE_BUT_H 30
#define STD_COURSE_W 100
#define STD_COURSE_H 75
#define STD_SLIDER_W 320
#define STD_SLIDER_H 10
#define TOP_BUT_POS_1 ofPoint(5 + (STD_BUT_W + 5)*0, 0)
#define TOP_BUT_POS_2 ofPoint(5 + (STD_BUT_W + 5)*1, 0)
#define TOP_BUT_POS_3 ofPoint(5 + (STD_BUT_W + 5)*2, 0)
#define TOP_BUT_POS_4 ofPoint(5 + (STD_BUT_W + 5)*3, 0)
#define SIDE_TOG_POS_1 ofPoint(0, 200 + (STD_TOG_SIZE + 5)*0)
#define SIDE_TOG_POS_2 ofPoint(0, 200 + (STD_TOG_SIZE + 5)*1)
#define SIDE_TOG_POS_3 ofPoint(0, 200 + (STD_TOG_SIZE + 5)*2)
#define SIDE_TOG_POS_4 ofPoint(0, 200 + (STD_TOG_SIZE + 5)*3 + 30)

//Define image locations
#define IMG_LOC_LOGO "images/logo.png"
#define IMG_LOC_BACK "images/buttons/back.png"
#define IMG_LOC_SAVE "images/buttons/save.png"
#define IMG_LOC_LOAD "images/buttons/load.png"
#define IMG_LOC_HELP "images/buttons/help.png"
#define IMG_LOC_DRAW "images/buttons/draw.png"
#define IMG_LOC_MOVE "images/buttons/move.png"
#define IMG_LOC_ERASE "images/buttons/erase.png"
#define IMG_LOC_CLEAR "images/buttons/clear.png"
#define IMG_LOC_PLAY "images/buttons/play.png"
#define IMG_LOC_CREATE "images/buttons/create.png"
#define IMG_LOC_CONFIG "images/buttons/config.png"
#define IMG_LOC_EXIT "images/buttons/exit.png"
#define IMG_LOC_SELECT_H "images/heading_select.png"
#define IMG_LOC_CREATE_H "images/heading_create.png"
#define IMG_LOC_CONFIG_H "images/heading_config.png"
#define IMG_LOC_HELP_CONFIG "images/config_help.png"
#define IMG_LOC_HELP_CREATE "images/create_help.png"


class gui {

    public:

        gui(){}

        void mouseMoved(int x, int y) {}

        bool mousePressed(int x, int y) {
            for (list<guiButton*>::iterator it = buttons.begin(); it != buttons.end(); it++) {
                if ((**it).mousePressed(x, y)) return true;
            }
            for (list<guiToggle*>::iterator it = toggles.begin(); it != toggles.end(); it++) {
                if ((**it).mousePressed(x, y)) return true;
            }
            for (list<guiTextField*>::iterator it = fields.begin(); it != fields.end(); it++) {
                if ((**it).mousePressed(x, y)) return true;
            }
            for (list<guiSlider*>::iterator it = sliders.begin(); it != sliders.end(); it++) {
                if ((**it).mousePressed(x, y)) return true;
            }
            for (list<guiInputWindow*>::iterator it = inputWindows.begin(); it != inputWindows.end(); it++) {
                if ((**it).mousePressed(x, y)) return true;
            }
            for (list<guiHelpWindow*>::iterator it = helpWindows.begin(); it != helpWindows.end(); it++) {
                if ((**it).mousePressed(x, y)) return true;
            }
            for (list<guiOptionGroup*>::iterator it = optionGroups.begin(); it != optionGroups.end(); it++) {
                if ((**it).mousePressed(x, y)) return true;
            }
            
            return false;
        }

        bool mouseDragged(int x, int y) {
            for (list<guiSlider*>::iterator it = sliders.begin(); it != sliders.end(); it++) {
                if ((**it).mouseDragged(x, y)) return true;
            }
            return false;
        }

        void keyPressed(int key) {
            for (list<guiTextField*>::iterator it = fields.begin(); it != fields.end(); it++) {
                (**it).keyPressed(key);
            }
            for (list<guiInputWindow*>::iterator it = inputWindows.begin(); it != inputWindows.end(); it++) {
                (**it).keyPressed(key);
            }
        }

        void draw() {
            ofSetRectMode(OF_RECTMODE_CORNER);
            for (list<guiButton*>::iterator it = buttons.begin(); it != buttons.end(); it++) {
                (**it).draw();
            }
            for (list<guiToggle*>::iterator it = toggles.begin(); it != toggles.end(); it++) {
                (**it).draw();
            }
            for (list<guiTextField*>::iterator it = fields.begin(); it != fields.end(); it++) {
                (**it).draw();
            }
            for (list<guiSlider*>::iterator it = sliders.begin(); it != sliders.end(); it++) {
                (**it).draw();
            }
            for (list<guiInputWindow*>::iterator it = inputWindows.begin(); it != inputWindows.end(); it++) {
                (**it).draw();
            }
            for (list<guiHelpWindow*>::iterator it = helpWindows.begin(); it != helpWindows.end(); it++) {
                (**it).draw();
            }
            for (list<guiOptionGroup*>::iterator it = optionGroups.begin(); it != optionGroups.end(); it++) {
                (**it).draw();
            }
        }

        void update() {
        }

        void add(guiButton* button) {
            buttons.push_back(button);
        }

        void add(guiToggle* toggle) {
            toggles.push_back(toggle);
        }

        void add(guiTextField* field) {
            fields.push_back(field);
        }

        void add(guiSlider* slider) {
            sliders.push_back(slider);
        }

        void add(guiInputWindow* window) {
            inputWindows.push_back(window);
        }

        void add(guiHelpWindow* window) {
            helpWindows.push_back(window);
        }

        void add(guiOptionGroup* group) {
            optionGroups.push_back(group);
        }

    private:

        list<guiButton*> buttons;
        list<guiToggle*> toggles;
        list<guiTextField*> fields;
        list<guiSlider*> sliders;
        list<guiInputWindow*> inputWindows;
        list<guiHelpWindow*> helpWindows;
        list<guiOptionGroup*> optionGroups;

};

#endif

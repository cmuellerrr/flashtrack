/*
 * config.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  The configuration screen of the application.
 * Configures the application to track either a determined color 
 * or threshold.
 *
 */

#pragma once
//#ifndef _CONFIG_H
//#define _CONFIG_H

#include "ofMain.h"
#include "tracker.h"
#include "gui.h"
#include "XMLUtil.h"

class configuration : public ofBaseApp {

    public:

        configuration();
        virtual ~configuration();

        void setup(tracker* t, ofBaseApp* p);
        void update();
        void draw();

        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);

    private:

        void setupGUI();

        ofBaseApp* parent;
        tracker* _tracker;
        XMLUtil xml;      
  
        ofImage header;

        gui GUI, lightGUI, manualGUI;
        guiSlider thresholdSlider, hueSlider, saturationSlider, valueSlider;
        guiButton backBut, saveBut, helpBut;
        guiOption lightOp, manualOp;
        guiOptionGroup trackOptions;
        guiHelpWindow helpWindow;
};

//#endif // CONFIG_H

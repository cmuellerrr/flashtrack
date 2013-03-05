/*
 * tracker.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  The tracker.  Analyzes the video 
 * feed and determines the location of the area that 
 * has been configured to be tracked.  Can either 
 * track a light source or any selected color.
 *
 */

#ifndef _TRACKER_H
#define _TRACKER_H

#include "ofxOpenCv.h"

enum{LIGHT, MANUAL};

class tracker {

    public:

        tracker();
        virtual ~tracker();

        void setup(int _width, int _height, int _screenWidth, int _screenHeight);
        void update();
        void draw();
        void resized(int w, int h);

        ofxCvColorImage* getColorData();
        ofxCvGrayscaleImage* getGrayscaleData();
        ofxCvGrayscaleImage* getThresholdData();
        ofxCvContourFinder*  getContours();
        int* getThreshold();
        float getX();
        float getY();
        int* getHueRange();
        int* getSaturationRange();
        int* getValueRange();
        int* getHue();
        int* getSaturation();
        int* getValue();
        void setThreshold(int _value);
        void setHueRange(int _value);
        void setSaturationRange(int _value);
        void setValueRange(int _value);
        void setHue(int _value);
        void setSaturation(int _value);
        void setValue(int _value);


        void setHueSatValByPixel(int pixel);

        int mode;

    private:
    
        ofVideoGrabber         vidGrabber;
        ofxCvContourFinder  contourFinder;

        ofxCvColorImage     capturedImageData;
        ofxCvColorImage     HSVImageData;
        ofxCvGrayscaleImage grayImageData;
        ofxCvGrayscaleImage thresholdImageData;
        ofxCvGrayscaleImage    grayHueData;
        ofxCvGrayscaleImage    graySaturationData;
        ofxCvGrayscaleImage    grayValueData;

        unsigned char *            grayPixels;
        
        int width, height, screenWidth, screenHeight, minArea, maxArea;
        int threshold;
        float lastX, lastY;
        int hue, saturation, value;
        int hueRange, saturationRange, valueRange;
};

#endif

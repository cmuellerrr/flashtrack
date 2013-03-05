/*
 * tracker.cpp
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

#include "tracker.h"

/*
 * Default constructor.
 */
tracker::tracker() {
    width = 360;
    height = 240;

    minArea = 2;
    maxArea = (int)(width * height * .33);

    threshold = 80;

    lastX = lastY = 0;
}

/*
 * Deleting the tracker.
 */
tracker::~tracker() {
}

/*
 * Sets up the tracker.  Sets the camera width/height, and the 
 * total screen width/height
 */
void tracker::setup(int _width, int _height, int _screenWidth, int _screenHeight) {
    width = _width;
    height = _height;
    screenWidth = _screenWidth;
    screenHeight = _screenHeight;

    maxArea = (int)(width * height * .33);

    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(width, height);

    capturedImageData.allocate(width, height);
    HSVImageData.allocate(width, height);
    grayImageData.allocate(width, height);
    thresholdImageData.allocate(width, height);
    grayHueData.allocate(width, height);
    graySaturationData.allocate(width, height);
    grayValueData.allocate(width, height);

    grayPixels = new unsigned char [width * height];

    mode = LIGHT;

    hueRange = 20;
    saturationRange = 30;
    valueRange = 25;
    
    hue = 0;
    saturation = 0;
    value = 0;
}

/*
 * Updates the tracker.  Depending on the mode, it searches through the 
 * video data looking for pixels that match the settings provided.  If 
 * a pixel matches, it is set to white, if not, it is set to black.  That 
 * new image goes to the contour finder, which finds holes.  The first 
 * contour is used as the area that is being tracked.
 */
void tracker::update() {
    lastX = getX();
    lastY = getY();
    vidGrabber.grabFrame();

    if (vidGrabber.isFrameNew()) {
        capturedImageData.setFromPixels(vidGrabber.getPixels(), width, height);
        capturedImageData.mirror(false, true);
        grayImageData.setFromColorImage(capturedImageData);

        //grayImageData.contrastStretch();

        if (mode == LIGHT) {        
            thresholdImageData = grayImageData;
            thresholdImageData.threshold(threshold);
        }
        else {
            HSVImageData = capturedImageData;
            HSVImageData.convertRgbToHsv();

            unsigned char * colorPixels = HSVImageData.getPixels();

            for (int i = 0; i < width*height; i++){
            
                // since hue is cyclical:
                int hueDiff = colorPixels[i*3] - hue;
                if (hueDiff < -127) hueDiff += 255;
                if (hueDiff > 127) hueDiff -= 255;
            
            
                if ((abs(hueDiff) < hueRange) &&
                    (colorPixels[i*3+1] > (saturation - saturationRange) && colorPixels[i*3+1] < (saturation + saturationRange)) &&
                    (colorPixels[i*3+2] > (value - valueRange) && colorPixels[i*3+2] < (value + valueRange))){
    
                    grayPixels[i] = 255;
        
                } else {
                    
                    grayPixels[i] = 0;
                }
                
            }
            thresholdImageData.setFromPixels(grayPixels, width, height);
        }

        thresholdImageData.dilate();
        thresholdImageData.blurHeavily();
        thresholdImageData.threshold(10);

        contourFinder.findContours(thresholdImageData, minArea, maxArea, 10, false, false);
    }
}

/*
 * Draws a circle at the current position being tracked.
 */
void tracker::draw() {
    ofPushStyle();
    ofNoFill();
    ofSetColor(255, 255, 255);
    ofCircle(getX(), getY(), 4);
    ofPopStyle();
}

/*
 * Changes the screen width/height when resized.
 */
void tracker::resized(int w, int h) {
   screenWidth = w;
   screenHeight = h;
}

/*
 * Returns the x position of the object being tracked.
 */
float tracker::getX() {
    if( contourFinder.nBlobs > 0 ) return (contourFinder.blobs[0].centroid.x / width) * screenWidth;
    return lastX;
}

/*
 * Returns the y position of the object being tracked.
 */
float tracker::getY() {
    if( contourFinder.nBlobs > 0 ) return (contourFinder.blobs[0].centroid.y / height) * screenHeight;
    return lastY;
}

/*
 * Returns a pointer to the initial video data.
 */
ofxCvColorImage* tracker::getColorData() {
    return &capturedImageData;
}

/*
 * Returns a pointer to a grascaled version of the video data.
 */
ofxCvGrayscaleImage* tracker::getGrayscaleData() {
    return &grayImageData;
}

/*
 * Returns a pointer to the black/white data that represents 
 * pixels that matched the settings.
 */
ofxCvGrayscaleImage* tracker::getThresholdData() {
    return &thresholdImageData;
}

/*
 * Returns a pointer to the contour finder.
 */
ofxCvContourFinder* tracker::getContours() {
    return &contourFinder;
}

/*
 * Returns a pointer to the threshold value.
 */
int* tracker::getThreshold() {
    return &threshold;
}

/*
 * Sets the threshold.
 */
void tracker::setThreshold(int _value) {
    threshold = _value;
}

/*
 * Returns a pointer to the hue range.
 */
int* tracker::getHueRange() {
    return &hueRange;
}

/*
 * Returns a pointer to the saturation range.
 */
int* tracker::getSaturationRange() {
    return &saturationRange;
}

/*
 * Returns a pointer to the value range.
 */
int* tracker::getValueRange() {
    return &valueRange;
}

/*
 * Returns a pointer to the target hue.
 */
int* tracker::getHue() {
    return &hue;
}

/*
 * Returns a pointer to the target saturation.
 */
int* tracker::getSaturation() {
    return &saturation;
}

/*
 * Returns a pointer to the target value.
 */
int* tracker::getValue() {
    return &value;
}

/*
 * Sets the hue range.
 */
void tracker::setHueRange(int _value) {
    hueRange = _value;
}

/*
 * Sets the saturation range.
 */
void tracker::setSaturationRange(int _value) {
    saturationRange = _value;
}

/*
 * Sets the value range.
 */
void tracker::setValueRange(int _value) {
    valueRange = _value;
}

/*
 * Sets the target hue.
 */
void tracker::setHue(int _value) {
    hue = _value;
}

/*
 * Sets the target saturation.
 */
void tracker::setSaturation(int _value) {
    saturation = _value;
}

/*
 * Sets the target value.
 */
void tracker::setValue(int _value) {
    value = _value;
}

/*
 * Sets the target hue, saturation, and value to that of the pixel
 * at the given position.
 */
void tracker::setHueSatValByPixel(int pixel) {
    if (pixel >=0 && pixel <= width * height) {
        HSVImageData.convertToGrayscalePlanarImages(grayHueData, graySaturationData, grayValueData);
        
        grayHueData.flagImageChanged();
        graySaturationData.flagImageChanged();
        grayValueData.flagImageChanged();

        hue = grayHueData.getPixels()[pixel];
        saturation = graySaturationData.getPixels()[pixel];
        value = grayValueData.getPixels()[pixel];
    }
}

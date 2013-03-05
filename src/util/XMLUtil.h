/*
 * XMLUtil.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description: A class that handles saving/loading xml
 * files.  Handles courses and settings.
 *
 */

#ifndef _XML_UTIL_H
#define _XML_UTIL_H

#include "ofxXmlSettings.h"
#include "course.h"
#include "tracker.h"

class XMLUtil {

    public:

        XMLUtil();
        void saveCourse(string courseName, course* _course);
        bool loadCourse(string courseName, course* _course);
        void saveSettings(tracker* _tracker);
        bool loadSettings(tracker* _tracker);
    
    private:

        ofxXmlSettings XML;
};

#endif

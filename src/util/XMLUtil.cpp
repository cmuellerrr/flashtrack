/*
 * XMLUtil.cpp
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description: A class that handles saving/loading xml
 * files.  Handles courses and settings.
 *
 */

#include "XMLUtil.h"

/*
 * Default constructor.
 */
XMLUtil::XMLUtil() {

}

/*
 * Saves a given course to an xml file specified by courseName.
 * i.e. courseName.xml
 */
void XMLUtil::saveCourse(string courseName, course* _course) {
    XML.clear();
    int tagNum = XML.addTag("course");
    XML.pushTag("course", tagNum);

    XML.addTag("name");
    XML.setValue("name", courseName, 0);

    XML.addTag("color");
    XML.setValue("color", "blue", 0);

    XML.addTag("completed");
    XML.setValue("completed", false, 0);

    tagNum = XML.addTag("start");
    XML.setValue("start:x", _course->start.x, tagNum);
    XML.setValue("start:y", _course->start.y, tagNum);

    tagNum = XML.addTag("finish");
    XML.setValue("finish:x", _course->finish.x, tagNum);
    XML.setValue("finish:y", _course->finish.y, tagNum);

    tagNum = XML.addTag("nodes");
    XML.pushTag("nodes", tagNum);

    int numNodes = _course->nodes.size();
    int nodeNum;
    if (numNodes > 0) {
        for (int i = 0; i < numNodes; i++) {
            nodeNum = XML.addTag("node");
            XML.setValue("node:x", _course->getNodeAt(i)->x, nodeNum);
            XML.setValue("node:y", _course->getNodeAt(i)->y, nodeNum);
        }
    }
    //pop nodes
    XML.popTag();

    tagNum = XML.addTag("edges");
    XML.pushTag("edges", tagNum);

    int numEdges = _course->edges.size();
    int edgeNum;
    if (numEdges > 0) {
        for (int i = 0; i < numEdges; i++) {
            edgeNum = XML.addTag("edge");
            XML.pushTag("edge", edgeNum);
            XML.addTag("p1");
            XML.setValue("p1:x", _course->getEdgeAt(i)->p1->x, 0);
            XML.setValue("p1:y", _course->getEdgeAt(i)->p1->y, 0);
            XML.addTag("p2");
            XML.setValue("p2:x", _course->getEdgeAt(i)->p2->x, 0);
            XML.setValue("p2:y", _course->getEdgeAt(i)->p2->y, 0);
            XML.popTag();
        }
    }

    //pop edges
    XML.popTag();
    
    //pop course
    XML.popTag();
    XML.saveFile("courses/" + courseName + ".xml");
}

/*
 * Loads a course specified by the given name into the 
 * given course pointer.
 */
bool XMLUtil::loadCourse(string courseName, course* _course) {
    _course->clearCourse();
    if (!XML.loadFile(courseName)) return false;

    XML.pushTag("course", 0);

    _course->start.x = XML.getValue("start:x", 0, 0);
    _course->start.y = XML.getValue("start:y", 0, 0);
    _course->finish.x = XML.getValue("finish:x", 0, 0);
    _course->finish.y = XML.getValue("finish:y", 0, 0);

    XML.pushTag("nodes", 0);

    int numNodeTags = XML.getNumTags("node");
    for (int i = 0; i < numNodeTags; i++) {
        _course->addNode(ofPoint(XML.getValue("node:x", 0, i), XML.getValue("node:y", 0, i)));
    }

    //pop nodes
    XML.popTag();

    XML.pushTag("edges", 0);
    
    int numEdgeTags = XML.getNumTags("edge");
    for (int i = 0; i < numEdgeTags; i++) {
        ofPoint p1 = ofPoint(XML.getValue("edge:p1:x", 0, i), XML.getValue("edge:p1:y", 0, i)); 
        ofPoint p2 = ofPoint(XML.getValue("edge:p2:x", 0, i), XML.getValue("edge:p2:y", 0, i));
        _course->addEdge(_course->getNodeWithPos(p1), _course->getNodeWithPos(p2));
    }

    //pop edges
    XML.popTag();

    _course->setColor(XML.getValue("color", "blue", 0));

    //pop course
    XML.popTag();
    return true;
}

/*
 * Saves a tracker's settings to configuration.xml.
 */
void XMLUtil::saveSettings(tracker* _tracker) {
    XML.clear();
    int tagNum = XML.addTag("configuration");
    XML.pushTag("configuration", tagNum);

    tagNum = XML.addTag("tracker");
    XML.setValue("tracker:mode", _tracker->mode, tagNum);
    XML.setValue("tracker:threshold", *_tracker->getThreshold(), tagNum);
    XML.setValue("tracker:hue", *_tracker->getHue(), tagNum);
    XML.setValue("tracker:saturation", *_tracker->getSaturation(), tagNum);
    XML.setValue("tracker:value", *_tracker->getValue(), tagNum);
    XML.setValue("tracker:hueRange", *_tracker->getHueRange(), tagNum);
    XML.setValue("tracker:saturationRange", *_tracker->getSaturationRange(), tagNum);
    XML.setValue("tracker:valueRange", *_tracker->getValueRange(), tagNum);

    //pop configuration
    XML.popTag();
    XML.saveFile("settings/configuration.xml");
}

/*
 * Loads the settings from configuration.xml into the given 
 * tracker pointer.
 */
bool XMLUtil::loadSettings(tracker* _tracker) {
    if(!XML.loadFile("settings/configuration.xml")) return false;

    _tracker->mode = XML.getValue("configuration:tracker:mode", LIGHT, 0);
    _tracker->setThreshold(XML.getValue("configuration:tracker:threshold", 0, 0));
    _tracker->setHue(XML.getValue("configuration:tracker:hue", 0, 0));
    _tracker->setSaturation(XML.getValue("configuration:tracker:saturation", 0, 0));
    _tracker->setValue(XML.getValue("configuration:tracker:value", 0, 0));
    _tracker->setHueRange(XML.getValue("configuration:tracker:hueRange", 20, 0));
    _tracker->setSaturationRange(XML.getValue("configuration:tracker:saturationRange", 30, 0));
    _tracker->setValueRange(XML.getValue("configuration:tracker:valueRange", 25, 0));

    return true;
}

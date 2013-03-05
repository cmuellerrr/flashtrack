/*
 * creator.cpp
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  The course creation screen of the application.
 * Allows a user to create courses of their own.  They can draw, 
 * move, and erase nodes and edges.  They can also load previous 
 * levels to edit.
 *
 */

#include "creator.h"
#include "stdio.h"
#include "math.h"
#include "screenManager.h"

/**
 * Default constructor.
 */
creator::creator() {
    hasCandidate = false;
    hasIntersect = false;

    selected = 0;
    candidate = 0;
    base = 0;

    temp = ofPoint(0);
    intersect = ofPoint(0);

    mode = 0;
}

/**
 * Sets up the creator app.  Sets tracker, parent, and GUI.
 */
void creator::setup(tracker* t, ofBaseApp* p) {
    _tracker = t;
    parent = p;

    header.loadImage(IMG_LOC_CREATE_H);

    setupGUI();
}

/**
 * Creation of GUI elements.  Uses custom GUI classes.
 */
void creator::setupGUI() {
    backBut = guiButton("Back", TOP_BUT_POS_1, STD_BUT_W, STD_BUT_H, IMG_LOC_BACK);
    saveBut = guiButton("Save", TOP_BUT_POS_2, STD_BUT_W, STD_BUT_H, IMG_LOC_SAVE);    
    loadBut = guiButton("Load", TOP_BUT_POS_3, STD_BUT_W, STD_BUT_H, IMG_LOC_LOAD);
    helpBut = guiButton("Help", TOP_BUT_POS_4, STD_BUT_W, STD_BUT_H, IMG_LOC_HELP);
    clearBut = guiButton("", SIDE_TOG_POS_4, STD_TOG_SIZE, STD_TOG_SIZE, IMG_LOC_CLEAR);
    GUI.add(&backBut);
    GUI.add(&saveBut);
    GUI.add(&loadBut);
    GUI.add(&helpBut);
    GUI.add(&clearBut);

    drawOp = guiOption("Draw", SIDE_TOG_POS_1, STD_TOG_SIZE, STD_TOG_SIZE, DRAWING, IMG_LOC_DRAW);
    drawOp.setActive(true);
    moveOp = guiOption("Move", SIDE_TOG_POS_2, STD_TOG_SIZE, STD_TOG_SIZE, MOVING, IMG_LOC_MOVE);
    eraseOp = guiOption("Erase", SIDE_TOG_POS_3, STD_TOG_SIZE, STD_TOG_SIZE, ERASING, IMG_LOC_ERASE);
    createOptions.setValue(&mode);
    createOptions.add(&drawOp);
    createOptions.add(&moveOp);
    createOptions.add(&eraseOp);
    GUI.add(&createOptions);

    saveWindow = guiInputWindow("Enter a name for your course.");
    loadWindow = guiInputWindow("Enter the name of the course you are loading.");

    GUI.add(&saveWindow);
    GUI.add(&loadWindow);

    helpWindow = guiHelpWindow(IMG_LOC_HELP_CREATE);
    GUI.add(&helpWindow);
}

/**
 * Update the creator.  Doen't need to be updated apart from input events.  
 * Input events are handled in other functions.
 */
void creator::update() {    

}


/**
 * Draws the course being created, GUI, and temporary point being drawn (if any).
 */
void creator::draw() {
    ofPushStyle();
    header.draw(ofGetWidth()/2-header.getWidth()/2, 0);
    currentCourse.draw();

    //if the temp point is being used, draw it.
    if (base != 0 && temp.x != 0 && temp.y != 0) {
        edge tempEdge = edge(base, &temp);
        tempEdge.draw(currentCourse.getEdgeImage());
        ofSetRectMode(OF_RECTMODE_CENTER);
        currentCourse.getNodeImage()->draw(temp.x, temp.y, NODE_SIZE, NODE_SIZE);
    }

    ofNoFill();
    ofSetLineWidth(SELECT_WIDTH);
    ofSetColor(0, 0, 255);
    if (mode == MOVING) ofSetColor(255, 255, 0);
    if (mode == ERASING) ofSetColor(255, 0, 0);

    if (hasCandidate) {
        //if the candidate is the start or finish, make the selection circle larger.
        if (*candidate == currentCourse.start || *candidate == currentCourse.finish) {
            ofCircle(candidate->x, candidate->y, IMP_NODE_SIZE + 4);
        }
        else {
            ofCircle(candidate->x, candidate->y, NODE_SIZE);
        }
    }
    if (hasIntersect) {
        ofCircle(intersect.x,intersect.y, NODE_SIZE);
    }

    GUI.draw();
    ofPopStyle();
}

/**
 * Sends key presses to the GUI.
 */
void creator::keyPressed  (int key) {
    GUI.keyPressed(key);
}

/**
 * On mouse movement, finds any candidate nodes or edges.
 */
void creator::mouseMoved(int x, int y ) {
    findCandidate(x, y);
    intersectingEdge = findIntersectingEdge(x, y);
}

/**
 * First looks for candidate nodes or edges.  If the GUI wasnt dragged on,
 * either the selected point is moved to the mouse position (when in MOVE mode) 
 * or the temp point is moved to the mouse position (when in DRAW mode).
 */
void creator::mouseDragged(int x, int y, int button) {
    mouseMoved(x, y);
    if (!GUI.mouseDragged(x, y)) {
        if (mode == MOVING) {
            if (selected != 0) {
                currentCourse.updateNode(selected, x, y);
            }
        }
        else {
            if (mode != ERASING) {
                   temp.x = x;
                temp.y = y;
            }
        }
    }
}

/**
 * If the GUI wasnt clicked on, handles mouse clicks.
 * When MOVING, sets the selected point to the candidate node or creates 
 * an intermediate node on the candidate edge.
 * When ERASING, erases the candidate node or edge.
 * When DRAWING, either starts a line from the candidate node or intermediate 
 * node on the candidate edge, or starts a new line altogether.
 */
void creator::mousePressed(int x, int y, int button) {
    if (!mousePressedGUI(x, y)) {
        if (mode == MOVING) {
            if (hasCandidate) {
                selected = candidate;
                hasCandidate = false;
            }
            if (hasIntersect) {
                selected = currentCourse.addNode(intersect);
                currentCourse.addIntermediateNode(intersectingEdge, selected);
                hasIntersect = false;
            }
        } 
        else if (mode == ERASING) {
            if (hasCandidate) {
                currentCourse.deleteNode(candidate);
                candidate = 0;
                hasCandidate = false;
            }
            if (hasIntersect) {
                currentCourse.deleteEdge(intersectingEdge);
                intersectingEdge = 0;
                intersect = ofPoint(0);
                hasIntersect = false;
            }
        }
        else {
            if (hasCandidate) {
                base = candidate;
                hasCandidate = false;
            }
            else if (hasIntersect) {
                base = currentCourse.addNode(intersect);
                currentCourse.addIntermediateNode(intersectingEdge, base);
                hasIntersect = false;
            }
            else {
                base = currentCourse.addNode(ofPoint(x, y));
            }
        }
    }
}

/**
 * Sets the selected or temporary node to the current position.
 * If there is a candidate node or edge, the node being moved/drawn 
 * is merged with the candidate or an intermediate node on the 
 * candidate edge.
 */
void creator::mouseReleased(int x, int y, int button) {
    if (mode == MOVING) {
        if (hasCandidate && selected != 0) {
            currentCourse.mergeNodes(candidate, selected);
            hasCandidate = false;
        }
        if (hasIntersect && selected != 0) {
            currentCourse.addIntermediateNode(intersectingEdge, selected);
            hasIntersect = false;
        }
        selected = 0;
    }
    else {
        if (mode != ERASING && base != 0) {
            if (hasCandidate) {
                currentCourse.addEdge(base, candidate);
                hasCandidate = false;
            }
            else if (hasIntersect && intersect != ofPoint(0) && intersectingEdge != 0) {
                ofPoint* newNode = currentCourse.addNode(intersect);
                currentCourse.addEdge(base, newNode);
                currentCourse.addIntermediateNode(intersectingEdge, newNode);
                hasIntersect = false;
            }
            else {
                if (temp != ofPoint(0)) currentCourse.addEdge(base, currentCourse.addNode(ofPoint(temp)));
            }
            
        }
        base = 0;
        temp = ofPoint(0);
        intersect = ofPoint(0);
    }
}

/**
 * Handles GUI mouse presses.  Each element must be checked 
 * individually.  Initially, I designed my GUI classes to take 
 * functions as parameters to be called when the element is clicked.
 * I had to ditch this because passing member functions caused 
 * unneccessary problems.
 */
bool creator::mousePressedGUI(int x, int y) {
    bool result = GUI.mousePressed(x, y);
    if (backBut.checkHit(x, y)) {
        ((screenManager*)parent)->setMode(TITLE);
    }

    if (clearBut.checkHit(x, y)) {
        currentCourse.clearCourse();
    }

    if (saveBut.checkHit(x, y)) {
        helpWindow.hide();
        loadWindow.hide();
        saveWindow.show();
    }

    if (saveWindow.checkOK(x, y)) {
        xml.saveCourse("user/" + saveWindow.getField()->getText(), &currentCourse);
        saveWindow.hide();
    }

    if (loadBut.checkHit(x, y)) {
        helpWindow.hide();
        saveWindow.hide();
        loadWindow.show();
    }

    if (loadWindow.checkOK(x, y)) {
        xml.loadCourse("courses/user/" + loadWindow.getField()->getText() + ".xml", &currentCourse);
        loadWindow.hide();
    }
    if (helpBut.checkHit(x, y)) {
        loadWindow.hide();
        saveWindow.hide();
        helpWindow.show();
    }
    return result;
}

/**
 * Finds a candidate node.  Checks to see if the given mouse 
 * position is close enough to any node in the course.
 */
void creator::findCandidate(int x, int y) {
    hasCandidate = false;
    candidate = 0;
    
    for (list<ofPoint>::iterator it = currentCourse.nodes.begin(); it != currentCourse.nodes.end(); it++) {    
        if (selected != &*it && abs(it->x - x) < NODE_SIZE && abs(it->y - y) < NODE_SIZE) {
            candidate = &*it;
            hasCandidate = true;
        }
    }
    //Only check the start and finish nodes when in MOVING mode.
    if (mode == MOVING && selected == 0) {
        if (abs(currentCourse.start.x - x) < IMP_NODE_SIZE && abs(currentCourse.start.y - y)< IMP_NODE_SIZE) {
            candidate = &currentCourse.start;
            hasCandidate = true;
        }
        if (abs(currentCourse.finish.x - x) < IMP_NODE_SIZE && abs(currentCourse.finish.y - y) < IMP_NODE_SIZE) {
            candidate = &currentCourse.finish;
            hasCandidate = true;
        }
    }
}

/**
 * Finds poits on edges that are close enough to the given 
 * mouse position.  If one is found, that intersection point
 * is stored and a pointer to that edge is returned.
 */
edge* creator::findIntersectingEdge(int x, int y) {
    hasIntersect = false;
    intersect = ofPoint(0);
    if (!hasCandidate) {
        double yInt = 0;
        for (list<edge>::iterator it = currentCourse.edges.begin(); it != currentCourse.edges.end(); it++) {
            if (it->withinBounds(x, y, NODE_SIZE) && !containsEdge(currentCourse.getAssocEdges(selected), &*it)) {
                //Have to handle horizontal and vertical lines as separate
                //cases because of slope issues.
                if (it->xAxis) {
                    intersect.x = x;
                    intersect.y = it->p1->y;
                }
                else if (it->yAxis) {
                    intersect.x = it->p1->x;
                    intersect.y = y;
                }
                else {
                     yInt = y + (it->slope * x);
                    intersect.x = (yInt - it->yIntercept) / (2 * it->slope);
                    intersect.y = (-1 * it->slope * intersect.x) + yInt;
                }
                if (sqrt(pow(x - intersect.x, 2) + pow(y - intersect.y, 2)) < NODE_SIZE)  {
                    hasIntersect = true;    
                    return &*it;
                }
            }
        }
    }
    return 0;
}

/**
 * Returns whether or not the vector of edges contains the 
 * given edge. 
 * Should probably be moved to a different class.
 */
bool creator::containsEdge(vector<edge*> edges, edge* e) {
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i] == e) return true;
    }
    return false;
}

/**
 * Resets the creator app.
 */
void creator::reset() {
    currentCourse = course();

    hasCandidate = false;
    hasIntersect = false;

    selected = 0;
    candidate = 0;
    base = 0;

    temp = ofPoint(0);
    intersect = ofPoint(0);

    mode = DRAWING;
    drawOp.setActive(true);
    moveOp.setActive(false);
    eraseOp.setActive(false);

    loadWindow.hide();
    saveWindow.hide();
    helpWindow.hide();
}

/*
 * course.cpp
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  An object representing a course.  Consists 
 * of a start, finish, nodes, and edges.  Contains utility 
 * methods for adding, deleting, and updating nodes/edges.
 *
 */

#include "course.h"
#include "math.h"

/*
 * Default constructor.
 */
course::course() {
    start = ofPoint(200, 400);
	finish = ofPoint(ofGetWidth()-200, 400);
	startImg.loadImage("images/start.png");
	//startImg.resize(IMP_NODE_SIZE, IMP_NODE_SIZE);
	finishImg.loadImage("images/finish.png");
	//finishImg.resize(IMP_NODE_SIZE, IMP_NODE_SIZE);
	nodeImg.loadImage("images/node_blue.png");
	edgeImg.loadImage("images/edge_blue.png");
}

/*
 * Deleting the course. 
 */
course::~course() {

}

/*
 * Draws the current course.
 */
void course::draw() {
    ofSetRectMode(OF_RECTMODE_CENTER);
	ofSetLineWidth(EDGE_WIDTH);
	ofFill();
	ofSetColor(255, 255, 255);

	//Draw start and finish
	//ofSetColor(0, 255, 0);
	//ofCircle(start.x, start.y, IMP_NODE_SIZE);
	//ofSetColor(255, 0, 0);
	//ofCircle(finish.x, finish.y, IMP_NODE_SIZE);

	startImg.draw(start.x, start.y);
	finishImg.draw(finish.x, finish.y);
 
    //Draw nodes
    ofSetColor(255, 255, 255);
	for (list<ofPoint>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		//ofRect(it->x, it->y, NODE_SIZE, NODE_SIZE);
		nodeImg.draw(it->x, it->y, NODE_SIZE, NODE_SIZE);
	}
	//Draw edges
	for (list<edge>::iterator it = edges.begin(); it != edges.end(); it++) {
		//ofLine(it->p1->x, it->p1->y, it->p2->x, it->p2->y);
		it->draw(&edgeImg);
	}
}

/*
 * Adds the given node to the course's node list.
 */
ofPoint* course::addNode(ofPoint node) {
	nodes.push_back(node);
	//std::cout<<"# nodes "<<nodes.size()<<'\n';
    return &nodes.back();
}

/*
 * Deletes the node referenced by the given pointer.
 */
void course::deleteNode(ofPoint* node) {
	deleteAssocEdges(node);
    int index = getNodeIndex(node);
    list<ofPoint>::iterator it = nodes.begin();
	if (index >= 0) {
		advance(it, index);
		nodes.erase(it);
	}
	//std::cout<<"# nodes "<<nodes.size()<<'\n';
}

/*
 * Updates the given node with the position (x, y)
 */
ofPoint* course::updateNode(ofPoint* node, int x, int y) {
    node->x = x;
	node->y = y;
	updateAssocEdges(node);
    return node;
} 

/*
 * Returns a pointer to a node that is located at the given position.
 * If no such node exists, a pointer to nothing is returned.
 */
ofPoint* course::getNodeWithPos(ofPoint position) {
    for (list<ofPoint>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		if (*it == position) return &*it;
	}
	return 0;
}

/*
 * Returns a reference to the node at the given index.
 */
ofPoint* course::getNodeAt(int index) {
    list<ofPoint>::iterator it = nodes.begin();
	advance(it, index);
	return &*it;
}

/*
 * Gets the index of the referenced node.
 */
int course::getNodeIndex(ofPoint* node) {
	int index = 0;
	for (list<ofPoint>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		if (&*it == node) return index;
		index++;
	}
	return -1;
}

/*
 * Merges the node referenced by mergee onto that referenced by base.
 * Merges the two node's edges and consequently deletes mergee from the 
 * node list.  Removes any duplicate edges.
 */
ofPoint* course::mergeNodes(ofPoint* base, ofPoint* mergee) {
    mergeEdges(base, mergee);
    deleteNode(mergee);
	removeDuplicateEdges();
	updateAssocEdges(base);
	return base;
}

/*
 * Adds an edge between the two referenced nodes.
 */
void course::addEdge(ofPoint* p1, ofPoint* p2) {
    edge newEdge = edge(p1, p2);
	edges.push_back(newEdge);
	//std::cout<<"# edges "<<edges.size()<<'\n';
}

/*
 * Deletes all edges that contain the referenced node.
 */
void course::deleteAssocEdges(ofPoint* node) {
	vector<edge*> assoc = getAssocEdges(node);
	for (int i = 0; i < assoc.size(); i++) {
		deleteEdge(assoc[i]);
	}
}

/*
 * Updates all edges associated with the given node.
 */
void course::updateAssocEdges(ofPoint* node) {
    vector<edge*> assoc = getAssocEdges(node);
	for (int i = 0; i < assoc.size(); i++) {
		assoc[i]->update();
	}
}

/*
 * Gets all edges associated with the given node.
 */
vector<edge*> course::getAssocEdges(ofPoint* node) {
	vector<edge*> assoc;
	for (list<edge>::iterator it = edges.begin(); it != edges.end(); it++) {
		if (it->p1 == node || it->p2 == node) assoc.push_back(&*it);
	}
	return assoc;
}

/*
 * Deletes the referenced edge from the edge list.
 */
void course::deleteEdge(edge* e) {
    int index = getEdgeIndex(e);
	list<edge>::iterator it = edges.begin();
	if (index >= 0) {
		advance(it, index);
		edges.erase(it);
	}
	//std::cout<<"# edges "<<edges.size()<<'\n';
}

/*
 * Returns the edge located at the given index.
 */
edge* course::getEdgeAt(int index) {
    list<edge>::iterator it = edges.begin();
	advance(it, index);
	return &*it;
}

/*
 * Retruns the index, in the edge list, of the edge referenced by e.
 */
int course::getEdgeIndex(edge* e) {
	int index = 0;
    for (list<edge>::iterator it = edges.begin(); it != edges.end(); it++) {
		if (&*it == e) return index;
		index++;
	}
	return -1;
}

/*
 * Merges the edges of mergee with that of base.  Any edge that contains a 
 * reference to mergee replaces mergee with base.
 */
ofPoint* course::mergeEdges(ofPoint* base, ofPoint* mergee) {
    for (list<edge>::iterator it = edges.begin(); it != edges.end(); it++) {
		if (it->p1 == mergee) it->p1 = base;
		if (it->p2 == mergee) it->p2 = base;
	}
    return base;
}

/*
 * Removes duplicate edges from the edge list.  
 * Really a pretty backwards way of doing it. I don't like it 
 * but iterators don't allow simple arithmetic.
 */
void course::removeDuplicateEdges() {
    vector<edge*> duplicates;
	int count = 0;
	for (list<edge>::iterator it = edges.begin(); it != edges.end(); it++) {
		for (list<edge>::iterator er = it; er != edges.end(); er++) {
			if (it->p1 == er->p1 && it->p2 == er->p2 || 
				it->p1 == er->p2 && it->p2 == er->p1) {
				count++;
				if (count > 1) {
				    duplicates.push_back(&*it);
				}
			}
		}
		count = 0;
	}
	for (int i = 0; i < duplicates.size(); i++) {
        deleteEdge(duplicates[i]);  
	}
}

/*
 * Creates an edge between that which is referenced by e.  
 * If given edge {a, b} and node c, this method creates 
 * edges {a, c} and {c, b}. 
 */
ofPoint* course::addIntermediateNode(edge* e, ofPoint* node) {
    edge newEdge = edge(node, e->p2);
	edges.push_back(newEdge);
	e->p2 = node;
	e->update();
	removeDuplicateEdges();
	return node;
}

/*
 * Sets the start position.
 */
void course::setStart(ofPoint pos) {
    start = pos;
}

/*
 * Sets the finish position.
 */
void course::setFinish(ofPoint pos) {
    finish = pos;
}

/*
 * Clears the node and edge lists.
 */
void course::clearCourse() {
    nodes.clear();
	edges.clear();
}

/*
 * Sets the courses color.
 */
void course::setColor(string color) {
	nodeImg.loadImage("images/node_" + color + ".png");
    edgeImg.loadImage("images/edge_" + color + ".png");
}

/*
 * Returns a pointer to the node image.
 */
ofImage* course::getNodeImage() {
    return &nodeImg;
}

/*
 * Returns a pointer to the edge image.
 */
ofImage* course::getEdgeImage() {
    return &edgeImg;
}

/*
 * course.h
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

#ifndef COURSE_H
#define COURSE_H

#define NODE_SIZE 12
#define IMP_NODE_SIZE 40
#define EDGE_WIDTH 20

#include "ofTypes.h"
#include "ofMain.h"
#include "edge.h"

class course {

    public:

        course();
        virtual ~course();

        course & operator=( const course& course ){
            start = course.start;
            finish = course.finish;
            nodes = course.nodes;
            edges = course.edges;
            return *this;
        }
        
        void draw();
        
        ofPoint* addNode(ofPoint node);
        void deleteNode(ofPoint* node);
        ofPoint* updateNode(ofPoint* node, int x, int y);
        ofPoint* getNodeWithPos(ofPoint position);
        ofPoint* getNodeAt(int index);
        int getNodeIndex(ofPoint* node);
        ofPoint* mergeNodes(ofPoint* base, ofPoint* mergee);

        void addEdge(ofPoint* p1, ofPoint* p2);
        void deleteAssocEdges(ofPoint* node);
        void updateAssocEdges(ofPoint* node);
        vector<edge*> getAssocEdges(ofPoint* node);
        void deleteEdge(edge* e);
        edge* getEdgeAt(int index);
        int getEdgeIndex(edge* e);
        ofPoint* mergeEdges(ofPoint* base, ofPoint* mergee);
        void removeDuplicateEdges();
        ofPoint* addIntermediateNode(edge* e, ofPoint* node);

        void clearCourse();

        ofImage* getNodeImage();
        ofImage* getEdgeImage();
        void setStart(ofPoint pos);
        void setFinish(ofPoint pos);
        void setColor(string color);
        
        ofPoint start;
        ofPoint finish;
        list<ofPoint> nodes;
        list<edge> edges;

    private:

        ofImage startImg;
        ofImage finishImg;
        ofImage nodeImg;
        ofImage edgeImg;
};

#endif // COURSE_H

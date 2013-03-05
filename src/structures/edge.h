/*
 * edge.h
 *
 * Author: Chris Mueller
 * Date: 5/4/10
 * Project: Flash Track
 *
 * Description:  An object representing an edge.  Contains 
 * pointers to two nodes, and information about the equation of 
 * the line.
 *
 */

#ifndef _EDGE_H
#define _EDGE_H

#include "ofTypes.h"
#include "math.h"

class edge {

    public:

        /*
         * Default constructor
         */
        edge() {
            p1 = 0;
            p2 = 0;
            xAxis = false;
            yAxis = false;
            slope = 0;
            yIntercept = 0;
            length = 0;
            theta = 0;
        }

        /*
         * Constructor setting the two reference points.
         */
        edge (ofPoint* _p1, ofPoint* _p2) {
            p1 = _p1;
            p2 = _p2;
            update();
        }

        /*
         * Updates the line information of the edge.
         * Puts the point with the lowest x as p1, find the slope, 
         * yIntercept, whether or not its a hor/ver line, its theta,
         * and length.
         */
        edge* update() {
            if (p2->x < p1->x) {
                ofPoint* temp = p1;
                p1 = p2;
                p2 = temp;
            }
            double xDif = p2->x - p1->x;
            double yDif = p2->y - p1->y;
            
            slope = (yDif) / (xDif);
            yIntercept = p1->y - (slope * p1->x);
            if (abs(xDif) < NODE_SIZE / 2) yAxis = true;
            else {yAxis = false;}
            if (abs(yDif) < NODE_SIZE / 2) xAxis = true;
            else {xAxis = false;}
            length = sqrt(pow(xDif, 2) + pow(yDif, 2));

            theta = atan(abs(yDif) / xDif) * 180 / PI;
            if (p2->y > p1->y) theta = 360 - theta;
            theta *= -1;

            return this;
        }

        /*
         * Draws the edge.
         */
        void draw(ofImage* img) {
            ofPushStyle();
            ofPushMatrix();
            //ofSetRectMode(OF_RECTMODE_CENTER);
            ofTranslate(p1->x, p1->y, 0);
            glRotatef(theta, 0, 0, 1);  
            //do the drawing
            ofSetColor(255, 255, 255);
            ofSetRectMode(OF_RECTMODE_CORNER);
            img->draw(0, -10, length, EDGE_WIDTH);
            ofPopMatrix();
            ofPopStyle();
        }

        /*
         * Returns if the point specified by (x,y) is withing the given 
         * bound of the edge.
         */
        bool withinBounds(int x, int y, int bound) {
            //we know that p1.x is less than p2.x
            if (x < p1->x - bound || x > p2->x + bound) return false;
            if (p1->y < p2->y) {
                if (y < p1->y - bound || y > p2->y + bound) return false;
            }
            else {
                if (y < p2->y - bound || y > p1->y + bound) return false;
            }
            return true;
        }

        /*
         * Returns if the given edge intersects with this one.
         */
        bool intersects(edge* e) {
            int intersectX;
            int intersectY;
            if (yAxis && e->yAxis) return false;
            else if (yAxis) {
                intersectX = p1->x;
            }
            else if (e->yAxis) {
                intersectX = e->p1->x;
            }
            else {intersectX = (e->yIntercept - yIntercept) / (slope - e->slope);}
            intersectY = (slope * intersectX) + yIntercept;
            return withinBounds(intersectX, intersectY, 0) && e->withinBounds(intersectX, intersectY, 0);
        }

        ofPoint* p1;
        ofPoint* p2;
        double slope, yIntercept, length, theta;
        bool xAxis, yAxis;
};

#endif

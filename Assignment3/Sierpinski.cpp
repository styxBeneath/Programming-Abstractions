/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include <cmath>
using namespace std;

void sierpinskiTriangle(int rank,double x,double y,double r,GWindow &window) {
	if (rank<0) {
		return;
	}

	GPoint point0;
	GPoint point1;
	GPoint point2;

	point0=window.drawPolarLine(x,y,r,60); // top point of the rectangle
	point1=window.drawPolarLine(point0.getX(),point0.getY(),r,300); // right point of the rectangle
	point2=window.drawPolarLine(point1.getX(),point1.getY(),r,180); // left point of the rectangle
	
	// coordinates of the three rectangles of the next rank
	double x0=point2.getX();
	double x1=(point2.getX()+point0.getX())/2;
	double x2=(point2.getX()+point1.getX())/2;
	double y0=point2.getY();
	double y1=(point2.getY()+point0.getY())/2;
	double y2=(point2.getY()+point1.getY())/2;
	
	// recursive step which draws three rectangles of the next rank
	sierpinskiTriangle(rank-1,x0,y0,r/2,window);
	sierpinskiTriangle(rank-1,x1,y1,r/2,window);
	sierpinskiTriangle(rank-1,x2,y2,r/2,window);

}



int main() {

	GWindow window;
	int rank;
	double r;
	

	cin>>rank;
	cin>>r;
	
	sierpinskiTriangle(rank,(window.getWidth()-r)/2,window.getHeight()/2+r*sqrt(3.0)/4,r,window);
	
	
	return 0;
}

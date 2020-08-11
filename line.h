/******************************************************************************
* File:    line.h
* Class:   COP 2001 202005
* Author:  Rachel Matthews
* Purpose: Definitions header file for a Line class that represents a calculated
* line based on user input
******************************************************************************/
#ifndef LINE_H
#define LINE_H

#include "point.h"

class Line
{
public:
	// ------------------------------------------------------------------------
	// constructors
	// ------------------------------------------------------------------------
	Line();								// default constructor	
	Line(Point* point1, Point* point2);	// takes in two Point pointers
	Line(Point* point, float slope);	// takes in one Point pointer and float slope

	// ------------------------------------------------------------------------
	// accessors (getters and setters)
	// ------------------------------------------------------------------------
	Point* getPoint1();
	Point* getPoint2();

	float getSlope();
	void  setSlope(float value);
	float getYIntercept();
	void  setYIntercept(float value);
	float getLength();
	void  setLength(float value);
	float getAngle();
	void  setAngle(float value);

	// ------------------------------------------------------------------------
	// member methods
	// ------------------------------------------------------------------------
	void slopeFrom2Point();
	void slopeIntercept();
	void lineLength();
	void lineAngle();
	void calculate();

private:

	Point point1;
	Point point2;
    float slope;
	float yIntercept;
	float length;
	float angle;
};

#endif


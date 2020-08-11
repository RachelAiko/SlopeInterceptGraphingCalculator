/******************************************************************************
* File:    point.h
* Class:   COP 2001 202005
* Author:  Rachel Matthews
* Purpose: Definitions header file for a point class that represents a point
* on a line
******************************************************************************/
#ifndef POINT_H
#define POINT_H

#include "opengl.h"

class Point
{
public:
	// ------------------------------------------------------------------------
	// constructors
	// ------------------------------------------------------------------------
	Point(); 					// default
	Point(float x, float y );	// property constructor
	Point(Point* point);	    // copy constructor

	// ------------------------------------------------------------------------
	// accessors (getters and setters)
	// ------------------------------------------------------------------------
	float   getX();
	void    setX(float value);
	float   getY();
	void    setY(float value);
	
	// ------------------------------------------------------------------------
	// member methods
	// ------------------------------------------------------------------------
	bool IsEmpty();


private:
	float x;
	float y;
};

#endif
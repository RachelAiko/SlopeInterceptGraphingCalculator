/******************************************************************************
* File:    line.cpp
* Class:   COP 2001 202005
* Author:  Rachel Matthews
* Purpose: Implementation file for a Line class that represents a calculated
* line based on user input
******************************************************************************/
#include "line.h"
#include "point.h"

#include <math.h>   // math library 

//-----------------------------------------------------------------------------
// Global space - constants
//-----------------------------------------------------------------------------
const float PI{ 3.14159265 };

// ----------------------------------------------------------------------------
// constructors
// ----------------------------------------------------------------------------
/******************************************************************************
 default consructor
 *****************************************************************************/
Line::Line()
{
     point1 = Point();
     point2 = Point();
     slope = 0.0f;
     yIntercept = 0.0f;
     length = 0.0f;
     angle = 0.0f;
}

 /******************************************************************************
  property consructor
 ******************************************************************************/
Line::Line(Point* point1, Point* point2)
{
    this->point1 = point1;
    this->point2 = point2;
    slope = 0.0f;
    yIntercept = 0.0f;
    length = 0.0f;
    angle = 0.0f;
}

Line::Line(Point* point, float slope)
{
    this->point1 = point;
    this->slope = slope;
    yIntercept = 0.0f;
    length = 0.0f;
    angle = 0.0f;
}

 // ----------------------------------------------------------------------------
 // accessors (getters and setters)
 // ----------------------------------------------------------------------------
Point* Line::getPoint1() { return &point1; }
Point* Line::getPoint2() { return &point2; }

float  Line::getSlope()  { return slope; }
void   Line::setSlope(float value) { slope = value; }

float  Line::getYIntercept() { return yIntercept; }
void   Line::setYIntercept(float value) { yIntercept = value; }

float  Line::getLength() { return length; }
void   Line::setLength(float value) { length = value; }

float  Line::getAngle() { return angle; }
void   Line::setAngle(float value) { angle = value; }

/******************************************************************************
calculates the value of the slope property
parameters:
returns:
   void
*******************************************************************************/
void Line::slopeFrom2Point()
{ 
    slope = (point2.getY() - point1.getY()) / (point2.getX() - point1.getX());
   
} // end slope


/******************************************************************************
calculates the value of the slope-intercept property
parameters:
returns:
   void
*******************************************************************************/
void Line::slopeIntercept()
{
    yIntercept = point1.getY() - (slope * point1.getX());
  
} // end slopeIntercept


/******************************************************************************
calculates the lenth of a line
parameters:
returns:
    void
*******************************************************************************/
void Line::lineLength()
{
    
    length = sqrt(pow(point2.getX()- point1.getX(), 2) + pow(point2.getY() - point1.getY(), 2));

} // end lineLength


/******************************************************************************
calculates the angle property from the top of the Y axis as a float
parameters:
returns:
    void
*******************************************************************************/
void Line::lineAngle()
{
    float theta{ 0 };

    theta = atan2((point2.getY() - point1.getY()), (point2.getX() - point1.getX()));
    angle = fmod(90.0 - double(theta * 180.0 / PI), 360);

} // end lineAngle


/******************************************************************************
calls other member methods to set the slope, y-intercept, point two for 
    point-slope form, length, and angle
parameters:
returns:   void
*******************************************************************************/
void Line::calculate()
{
   
    if (!point2.IsEmpty())  // two-point form
    {
        slopeFrom2Point();
        slopeIntercept();

    }
    if (point2.IsEmpty())   // slope-intercpt form
    {
       slopeIntercept();
      
       // set point two to x = 0 and y = y-intercept
       point2.setX(0);
       point2.setY(getYIntercept());
    }

    lineLength();
    lineAngle();

}// end calculate
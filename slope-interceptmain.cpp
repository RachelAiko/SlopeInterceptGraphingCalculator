/******************************************************************************
* File:    slopeIntercept.cpp
* Class:   COP 2001 202005
* Author:  Rachel Matthews
* Purpose: main application file for Final - Slope-intercept Project
******************************************************************************/
#include <iostream>

#include <math.h>   // math library 

#include <iomanip>  // allows setting precision of float values

#include "opengl.h" // graphics library
#include "point.h"  // point objects
#include "line.h"   // line object

//-----------------------------------------------------------------------------
// Global space - constants, functions, data structures, etc.
//-----------------------------------------------------------------------------
const int WINDOW_WIDTH{ 500 };
const int WINDOW_HEIGHT{ 500 };
const char* WINDOW_TITLE{ "Line Graph\0" };

enum Mode
{
	TWO_POINT = 1,
	POINT_SLOPE,
	EXIT,
};


//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
int getProblem();
Line get2Point();
Point getPoint();
Line getPointSlope();
void drawLine(Line* line);
void display2Pt(Line* line);
void displayPointSlope(Line* line);
void displayLine(Line* line);
void displaySlopeIntercept(Line* line);


int main()
{	
	Line line = Line();	  // initialize with default constructor

	int choice;

	do
	{

		choice = getProblem();

		switch (choice)
		{
		case Mode::TWO_POINT:
			line = get2Point();
		    line.calculate();

			displayLine(&line);
			display2Pt(&line);
			displaySlopeIntercept(&line);
			drawLine(&line);

			break;

		case Mode::POINT_SLOPE:
		   line =  getPointSlope();
		   line.calculate();

			displayLine(&line);
			displayPointSlope(&line);
			displaySlopeIntercept(&line);
			drawLine(&line);

			break;

		case Mode::EXIT:
			std::cout << '\t' << "Have a Nice Day!!" << std::endl;
			break;

		default:
			std::cout << '\t' << "Please enter a valid choice from 1 to 3" << '\n';

		} // end switch

	} while (choice != Mode::EXIT);

	char pause;
	std::cin >> pause;

	return 0; // echo %errorlevel%
} // end main


/******************************************************************************
displays user menu, and inputs function value of problem selected
parameters:
returns:
	choice - user selection from menu
*******************************************************************************/
int getProblem()
{
	int choice;
	std::cout << '\n' << '\t'
		<< "Select the form that you would like to convert to slope-intercept form:" << '\n';
	std::cout << '\t' << '\t'
		<< "	1.) Two-point form (you know the two points of the line)" << '\n';
	std::cout << '\t' << '\t'
		<< "	2.) Point-slope form (you know the line's slope and one point)" << '\n';
	std::cout << '\t' << '\t'
		<< "	3.) Exit" << '\n';
	std::cout << '\t' << " => ", std::cin >> choice;

	return choice;
} // end getProblem


/******************************************************************************
prompts user for two ponts of a line and stores points as a line object
parameters:
returns:
	Line	- a new line with two points populated
*******************************************************************************/
Line get2Point()
{
	Line line = Line();

	std::cout << '\n' << '\t' << "Enter the 1st point for the line: " << '\n';
	Point point1 = getPoint();

	std::cout << '\n' << '\t' << "Enter the 2nd point for the line: " << '\n';
	Point point2 = getPoint();

	line = Line(&point1,  &point2);

	return line;
} // end get2Point


/******************************************************************************
prompts user for point on line using X Y coordinates
parameters:
returns:
	Point   - returns a point givin by the user
*******************************************************************************/
Point getPoint()
{
	Point point;
	float xCoord = 0;
	float yCoord = 0;

	std::cout << '\t' << "Enter X and Y coordinates separated by spaces: ", 
		std::cin >> xCoord >> yCoord;

	point.setX(xCoord);
	point.setY(yCoord);

	return point;
} // end getPoint


/******************************************************************************
takes one point and the slope that define a line an returns line object
parameters:
returns:
	line   - returns a line with a given point  and slope
*******************************************************************************/
Line getPointSlope()
{
	Line line = Line();
	float slope;

	std::cout << '\n' << '\t' << "Enter a point on the line: " << '\n';
	Point point1 = getPoint();

	std::cout << '\n' << '\t' << "Enter the slope of the line: ", std::cin
		>> slope;

	line = Line(&point1, slope);

	return line;
} // end getPointSlope


/******************************************************************************
takes a line object and graphs the line on OpenGL window
parameters:
	line  -  calculated line
returns:
	void
*******************************************************************************/
void drawLine(Line* line) 
{
	// create graphic window for drawing
	OpenGL window = OpenGL(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	//  x and y axises
	float positionXAxis[2]{ 0, WINDOW_HEIGHT / 2 };
	float sizeXAxis[2]{ WINDOW_WIDTH, 1 };
	float positionYAxis[2]{ WINDOW_WIDTH / 2, 0 };
	float sizeYAxis[2]{ 1, WINDOW_HEIGHT };
	unsigned char colorAxis[4] = { 0, 0, 0, 0 };

	// calculated line
	Point point = line->getPoint1();
	float x = point.getX();
	float y = point.getY();
	float width = 2;
	float height = line->getLength();
	float angle = line->getAngle();
	unsigned char colorLine[4] = { 0, 162, 48, 191 };

	x += WINDOW_WIDTH / 2;

	y = WINDOW_HEIGHT / 2 - y;

	float linePosition[2]{ x, y };
	float lineSize[2]{ width, height };
	float rotation = line->getAngle() - 180;

	// baground color
	unsigned char colorBackground[4] = { 0, 232, 229, 144 };

	while (!window.isClosing())
	{
		window.clearWindow(reinterpret_cast<const unsigned char*>(colorBackground));

		// draw x-axis
		window.DrawSprite(positionXAxis, sizeXAxis, reinterpret_cast <const unsigned char*>
			(colorAxis));
		// draw y-axis
		window.DrawSprite(positionYAxis, sizeYAxis, reinterpret_cast <const unsigned char*>
			(colorAxis));

		// draw calculated line
		window.DrawSprite(linePosition, lineSize, reinterpret_cast <const unsigned char*>
			(colorLine), rotation, false);

		window.paintWindow();

		window.pollEvents();

	}

	return;
} // end drawLine


/******************************************************************************
takes a line object and displays the current value of its properties
parameters:
	line - calculated line
returns:
	void
*******************************************************************************/
void displayLine(Line* line)
{
	Point* point1 = line->getPoint1();
	Point* point2 = line->getPoint2();

	std::cout << '\n' << '\t' << "Line: ";
	std::cout << std::setprecision(3) << '\n' << '\t' << '\t' << "Point-1:  "
		<< "(" << point1->getX() << ", " << point1->getY() << ")" << '\t';
	std::cout << '\n' << '\t' << '\t' << "Point-2:  " << "(" << point2->getX() << ", "
		<< point2->getY() << ")";
	std::cout << '\n' << '\t' << '\t' << "   Slope = " << line->getSlope();
	std::cout << '\n' << '\t' << "     Y-Intercept = " << line->getYIntercept();
	std::cout << '\n' << '\t' << '\t' << "  Length = " << line->getLength();
	std::cout << '\n' << '\t' << '\t' << "   Angle = " << line->getAngle() << '\n';

	return;
} // end displayLine


/******************************************************************************
takes a line object and displays the two-point form of the line
parameters:
	line -  line object
returns:
	void
*******************************************************************************/
void display2Pt(Line* line)
{
	Point* point1 = line->getPoint1();
	Point* point2 = line->getPoint2();

	std::cout << '\n' << '\t' << "Two-point form: ";
	std::cout << '\n' << '\t' << '\t' << '\t' << "(" << point2->getY() << " - "
		<< point1->getY() << ")";
	std::cout << '\n' << '\t' << '\t' << "m = -------------------";
	std::cout << '\n' << '\t' << '\t' << '\t' << "(" << point2->getX()<< " - "
		<< point1->getX() << ")" << '\n';

	return;
} /// end display2Pt


/******************************************************************************
takes a line object and displays the point-slope form of the line
parameters:
	line -  line object
returns:
	void
*******************************************************************************/
void displayPointSlope(Line* line)
{
	Point* point1 = line->getPoint1();
	Point* point2 = line->getPoint2();

	std::cout << '\n' << '\t' << "Point-slope form: ";
	std::cout << std::setprecision(3) << '\n' << '\t' << '\t' << "y" << " - "
		<< point1->getY() << " = " << line->getSlope() << "(" << "x" << " - "
		<< point1->getX() << ")" << '\n';

	return;
} // end displayPointSlope


/******************************************************************************
takes a line object and displays the slope-intercept form of the line
parameters:
	line -  line object
returns:
	void
*******************************************************************************/
void displaySlopeIntercept(Line* line)
{
	std::cout << '\n' << '\t' << "Slope-intercept form: ";
	std::cout << std::setprecision(3) << '\n' << '\t' << '\t' << "y = " << line->getSlope()
		<< "x + " << line->getYIntercept() << '\n';

	return;
} // end displaySlopeIntercept
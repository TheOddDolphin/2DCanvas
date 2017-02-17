#pragma once
//necessary imports
#include "stdafx.h"
#include "freeglut.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Shape
{
public:
	vector<float> points; //stack of coordinates
	char type; //shape type - point, line, etc.

	//constructors
	//default
	Shape() {
		points.push_back(0); points.push_back(0);
		type = 's';
	}

	//constructor for points and circles
	Shape(float x, float y, char newType) {
		points.push_back(x); points.push_back(y);
		type = newType;
	}

	//constructor for quadrilateral Shapes
	Shape(float x1, float y1, float x2, float y2, char newType) {
		points.push_back(x1); points.push_back(y1);
		points.push_back(x2); points.push_back(y2);
		type = newType;
	}

	//constructor for triangle Shapes
	Shape(float x1, float y1, float x2, float y2, float x3, float y3, char newType) {
		points.push_back(x1); points.push_back(y1);
		points.push_back(x2); points.push_back(y2);
		points.push_back(x3); points.push_back(y3);
		type = newType;
	}

	//draw shapes
	void draw() {
		switch (type) {
		case 'p': //point
			glBegin(GL_POINTS);
			glVertex2f(points[0], points[1]);
			glEnd();
			break;
		case 'l': //line
			glBegin(GL_LINES);
			glVertex2f(points[0], points[1]);
			glVertex2f(points[2], points[3]);
			glEnd();
			break;
		case 'r': //rectangle - unfilled
			glBegin(GL_LINE_LOOP);
			glVertex2f(points[0], points[1]);
			glVertex2f(points[0], points[3]);
			glVertex2f(points[2], points[3]);
			glVertex2f(points[2], points[1]);
			glEnd();
			break;
		case 't': //triangle - unfilled
			glBegin(GL_LINE_LOOP);
			glVertex2f(points[0], points[1]);
			glVertex2f(points[2], points[3]);
			glVertex2f(points[4], points[5]);
			glEnd();
			break;
		case 'T': //triangle - filled
			glBegin(GL_TRIANGLES);
			glVertex2f(points[0], points[1]);
			glVertex2f(points[2], points[3]);
			glVertex2f(points[4], points[5]);
			glEnd();
			break;
		case 'R': //rectangle - filled
			glRectf(points[0], points[1], points[2], points[3]);
			break;
		case 'C': //circle - filled
			glBegin(GL_TRIANGLE_FAN);
			//calculate radius
			float r = sqrt(pow(points[2] - points[0], 2) + pow(points[3] - points[1], 2));
			//draw circle using parametric equations
			for (float t = 0; t < (M_PI * 2); t += 0.0001f) {
				float x = points[0] + (r * cos(t));
				if (x > 1.0f) {		//limit drawing so that it doesn't
					x = 1.0f;		//draw over the menus, or outside the viewport
				}
				if (x < -0.8f) {
					x = -0.8f;
				}
				float y = points[1] + (r * sin(t));
				if (y < -1.0f) {
					y = -1.0f;
				}
				if (y > 0.8f) {
					y = 0.8f;
				}
				glVertex2f(x, y);
			}
			glEnd();
		}
	}
};
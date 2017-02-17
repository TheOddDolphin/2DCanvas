// 2DCanvas.cpp : Defines the entry point for the console application.
//

//necessary included files
#include "stdafx.h"
#include "freeglut.h"
#include "Shape.h" //!!!!!Shape object declaration - used to store drawing data!!!!!
#define _USE_MATH_DEFINES
#include <cmath>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;

//necessary declarations
string title = "2DCanvas by 2015034"; //text at bottom of window
string releaseno = "1.0.0";
int width; //of window
int height; //of window
bool gridState = true; //grid on/off boolean
int select = 0; //icon selected
vector<Shape> shapes; //stack of shape objects
vector<float> buffer; //coordinates of object currently being drawn
int selected = 0; //currently selected object reference

//function called on window resize
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

//convert mouse x-coordinates to world x-coordinates
float mouseXToWorld(int mx) {
	float wx = (float)mx / (width / 2);
	wx -= 1.0f;
	return wx;
}

//convert mouse y-coordinates to world y-coordinates
float mouseYToWorld(int my) {
	float wy = (float)my / (height / 2);
	wy = -1.0f * wy;
	wy += 1.0f;
	return wy;
}

//general canvas initiating; used mainly as reset after drawing
void initCanvas() {
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);
	glPointSize(3);
	glLineWidth(1.0);
	glutPostRedisplay();
}

//function to draw dashed grid
void drawGrid() {
	if (gridState == true) {
		glColor3f(0.7, 0.7, 0.7);
		glBegin(GL_LINES);
		for (float f = -1.0f; f <= 1.0f; f += 0.2f) {
			for (float f1 = 1.0f; f1 >= -1.0f; f1 -= 0.04f) {
				glVertex2f(f, f1);
				glVertex2f(f, f1 - 0.02f);
				glVertex2f(f1, f);
				glVertex2f(f1 - 0.02f, f);
			}
		}
		glEnd();
		glColor3f(0, 0, 0);
	}
}

//grid menu (see below) option processing
void processGrid(int option) {
	switch (option) {
	case 1:
		gridState = true;
		glutPostRedisplay();
		break;
	case 2:
		gridState = false;
		glutPostRedisplay();
		break;
	}
}

//function to create the grid on/off menu
void createGridMenu() {
	int menu;
	menu = glutCreateMenu(processGrid);


	glutAddMenuEntry("Grid On", 1);
	glutAddMenuEntry("Grid Off", 2);


	glutAttachMenu(GLUT_RIGHT_BUTTON); //map menu spawn to right mouse button
}

//function to draw side menus and icons
void drawMenus() {
	glColor3f(0.2, 0.6, 0.8);
	glRectf(-0.8, 0.8, -1, -1);
	glRectf(-0.8, 0.8, 1, 1);
	glColor3f(0.35, 0.35, 0.67);
	glRectf(-0.8, 0.8, -1, 0);
	glRectf(-0.8, 0.8, -0.2, 1);
	initCanvas();
	glColor3f(0, 1, 0);
	switch (select) {
	case 1:
		glRectf(-0.8f, 0.8f, -1.0f, 0.6f);
		break;
	case 2:
		glRectf(-0.8f, 0.6f, -1.0f, 0.4f);
		break;
	case 3:
		glRectf(-0.8f, 0.4f, -1.0f, 0.2f);
		break;
	case 4:
		glRectf(-0.8f, 0.2f, -1.0f, 0.0f);
		break;
	case 5:
		glRectf(-0.8f, 0.8f, -0.6f, 1.0f);
		break;
	case 6:
		glRectf(-0.6f, 0.8f, -0.4f, 1.0f);
		break;
	case 7:
		glRectf(-0.4f, 0.8f, -0.2f, 1.0f);
		break;
	}
	initCanvas();
	glBegin(GL_LINES);
	glVertex2f(-0.8, 1); glVertex2f(-0.8, -1);
	glVertex2f(-1, 0.8); glVertex2f(1, 0.8);
	for (float i = 0.6; i >= 0; i -= 0.2) {
		glVertex2f(-0.8, i); glVertex2f(-1, i);
	}
	for (float i = -0.6; i <= -0.2; i += 0.2) {
		glVertex2f(i, 0.8); glVertex2f(i, 1);
	}
	glVertex2f(-0.85, 0.55); glVertex2f(-0.95, 0.45);
	glEnd();
	initCanvas();
	glBegin(GL_POINTS);
	glVertex2f(-0.9, 0.7);
	glEnd();
	initCanvas();
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.85, 0.35);
	glVertex2f(-0.85, 0.25);
	glVertex2f(-0.95, 0.25);
	glVertex2f(-0.95, 0.35);
	glEnd();
	initCanvas();
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.85, 0.15);
	glVertex2f(-0.85, 0.05);
	glVertex2f(-0.95, 0.05);
	glEnd();
	initCanvas();
	glRasterPos2f(-0.15, -0.95);
	glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)title.c_str());
	initCanvas();
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.75, 0.85);
	glVertex2f(-0.65, 0.85);
	glVertex2f(-0.65, 0.95);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(-0.55, 0.85);
	glVertex2f(-0.45, 0.85);
	glVertex2f(-0.45, 0.95);
	glVertex2f(-0.55, 0.95);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(-0.3, 0.9);
	for (float t = 0; t <= (2 * M_PI); t += 0.001) {
		glVertex2f((-0.3 + (0.05*cos(t))), (0.9 + (0.05*sin(t))));
	}
	glEnd();
	initCanvas();
}

//function to draw all shapes in shape stack
void drawShapes() {
	if (!(shapes.empty())) { //if stack is not empty
		for (int i = 0; i < shapes.size(); i++) {
			if (i == selected) {
				glColor3f(1.0, 0, 0); //highlight currently selected primitive
			}
			shapes[i].draw(); //call draw function of each Shape object in shapes vector
			glColor3f(0, 0, 0); //reset colour
			glutPostRedisplay();
		}
	}
}

//print some instructions in the console
void helpConsole() {
	stringstream title;
	title << "2DCanvas by 2015034\n"
		<< "release " << releaseno
		<< "\nHelp Document - last updated 08/11/2016\n\n";
	string s = title.str();
	printf_s(s.c_str());
	stringstream help;
	help << "DRAWING\n"
		<< "1) Left click on any icon in the horizontal and vertical menus to select it.\n"
		<< "2) Click within the canvas to draw the shape. Click once to draw points. Click\ntwice"
		<< " to draw all the other shapes and primitives.\n\n"
		<< "ERASING\n"
		<< "Press <spacebar> to erase all the primitives on the canvas.\n"
		<< "If you would like to erase one specific type of primitive, then instead hit the "
		<< "corresponding button:\n"
		<< "	'l' : clear all lines\n"
		<< "	't' : clear all triangles\n"
		<< "	'p' : clear all points\n"
		<< "	'c' : clear all circles\n"
		<< "	'r' : clear all rectangles\n\n"
		<< "SELECTING\n"
		<< "The currently selected primitive will always be highlighted in red.\n"
		<< "To cycle the currently selected primitive, press '[' and ']'.\n\n"
		<< "MOVING\n"
		<< "To move, the currently selected primitive around within the canvas, simply use\nthe "
		<< "arrow keys.\n\n"
		<< "GRID\n"
		<< "Right click within the canvas to open the grid menu. From the menu, you can\nchoose to"
		<< " hide or display the dashed grid.\n\n"
		<< "QUIT\n"
		<< "To quit, press <esc>.";
	s = help.str();
	printf_s(s.c_str());
}

//main display function for all of program
void mainCanvas() {
	drawGrid();
	drawMenus();
	drawShapes();
}

//mouseclick handler
void mouseClick(int button, int state, int x, int y) {
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		if (x < 50) { //if click in valid area
			if (y < 250) { //set selected icon accordingly
				buffer.clear();
				if ((y > 50) && (y < 100)) {
					if (select == 1) {		//if already selected
						select = 0;			//deselect
					}
					else { select = 1; }
				}
				if ((y > 100) && (y < 150)) {
					if (select == 2) {
						select = 0;
					}
					else { select = 2; }
				}
				if ((y > 150) && (y < 200)) {
					if (select == 3) {
						select = 0;
					}
					else { select = 3; }
				}
				if (y > 200) {
					if (select == 4) {
						select = 0;
					}
					else { select = 4; }
				}
			}
		} //menu selects
		if (y < 50) {
			if (x < 200) {
				buffer.clear();
				if ((x > 50) && (x < 100)) {
					if (select == 5) {
						select = 0;
					}
					else { select = 5; }
				}
				if ((x > 100) && (x < 150)) {
					if (select == 6) {
						select = 0;
					}
					else { select = 6; }
				}
				if (x > 150) {
					if (select == 7) {
						select = 0;
					}
					else { select = 7; }
				}
			}
		} //menu selects
		Shape s; //initialise placeholder
		if ((x > 50) && (y > 50)) {
			switch (select) {
			case 1:
				s = Shape(mouseXToWorld(x), mouseYToWorld(y), 'p');
				buffer.clear(); //clear buffer
				break;
			case 2:
				buffer.push_back(x); buffer.push_back(y); //send points to buffer stack
				if (buffer.size() == 4) { //if all necessary points have been input to buffer
					//write to a placeholder object
					s = Shape(mouseXToWorld(buffer[0]), mouseYToWorld(buffer[1])
						, mouseXToWorld(buffer[2]), mouseYToWorld(buffer[3]), 'l');
					buffer.clear(); //clear buffer
				}
				break;
			case 3:
				buffer.push_back(x); buffer.push_back(y);
				if (buffer.size() == 4) {
					s = Shape(mouseXToWorld(buffer[0]), mouseYToWorld(buffer[1])
						, mouseXToWorld(buffer[2]), mouseYToWorld(buffer[3]), 'r');
					buffer.clear();
				}
				break;
			case 4:
				buffer.push_back(x); buffer.push_back(y);
				if (buffer.size() == 6) {
					s = Shape(mouseXToWorld(buffer[0]), mouseYToWorld(buffer[1])
						, mouseXToWorld(buffer[2]), mouseYToWorld(buffer[3])
						, mouseXToWorld(buffer[4]), mouseYToWorld(buffer[5]), 't');
					buffer.clear();
				}
				break;
			case 5:
				buffer.push_back(x); buffer.push_back(y);
				if (buffer.size() == 6) {
					s = Shape(mouseXToWorld(buffer[0]), mouseYToWorld(buffer[1])
						, mouseXToWorld(buffer[2]), mouseYToWorld(buffer[3])
						, mouseXToWorld(buffer[4]), mouseYToWorld(buffer[5]), 'T');
					buffer.clear();
				}
				break;
			case 6:
				buffer.push_back(x); buffer.push_back(y);
				if (buffer.size() == 4) {
					s = Shape(mouseXToWorld(buffer[0]), mouseYToWorld(buffer[1])
						, mouseXToWorld(buffer[2]), mouseYToWorld(buffer[3]), 'R');
					buffer.clear();
				}
				break;
			case 7:
				buffer.push_back(x); buffer.push_back(y);
				if (buffer.size() == 4) {
					s = Shape(mouseXToWorld(buffer[0]), mouseYToWorld(buffer[1])
						, mouseXToWorld(buffer[2]), mouseYToWorld(buffer[3]), 'C');
					buffer.clear();
				}
				break;
			}
			if (buffer.empty() && (s.type != 's')) { //if buffer is empty and placeholder is full
				shapes.push_back(s); //send Shape to shapes stack
			}
		} //canvas click
	}
}

//keypress handlers
void specKeyPress(int key, int x, int y) {
	if (!shapes.empty()) {
		bool stop = false;
		switch (key) {
		case GLUT_KEY_UP:
			for (int i = 1; i < shapes[selected].points.size(); i += 2) {
				if (shapes[selected].points[i] > 0.8f) { //check boundary collision
					stop = true;
					i = shapes[selected].points.size();
				}
			}
			if (stop == false) { //if not on boundary
				for (int i = 1; i < shapes[selected].points.size(); i += 2) {
					shapes[selected].points[i] += 0.01f; //then move
				}
			}
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			for (int i = 1; i < shapes[selected].points.size(); i += 2) {
				if (shapes[selected].points[i] < -1.0f) {
					stop = true;
					i = shapes[selected].points.size();
				}
			}
			if (stop == false) {
				for (int i = 1; i < shapes[selected].points.size(); i += 2) {
					shapes[selected].points[i] -= 0.01f;
				}
			}
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			for (int i = 0; i < shapes[selected].points.size(); i += 2) {
				if (shapes[selected].points[i] > 1.0f) {
					stop = true;
					i = shapes[selected].points.size();
				}
			}
			if (stop == false) {
				for (int i = 0; i < shapes[selected].points.size(); i += 2) {
					shapes[selected].points[i] += 0.01f;
				}
			}
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:
			for (int i = 0; i < shapes[selected].points.size(); i += 2) {
				if (shapes[selected].points[i] < -0.8f) {
					stop = true;
					i = shapes[selected].points.size();
				}
			}
			if (stop == false) {
				for (int i = 0; i < shapes[selected].points.size(); i += 2) {
					shapes[selected].points[i] -= 0.01f;
				}
			}
			glutPostRedisplay();
			break;
		}
	}
}

void normKeyPress(unsigned char key, int x, int y) {
	switch (key) {
	case ' ': //erase all
		shapes.clear();
		buffer.clear();
		selected = 0;
		break;
	case 27: //quit
		exit(0);
	//code to erase specific primitives one by one
	case 'p': //erase all points
	case 'l': //erase all lines
	case 'r': //erase all squares
	case 't': //erase all triangles
	case 'c': //erase all circles
		for (int i = 0; i < shapes.size(); i++) {
			if (tolower(shapes[i].type) == key) {
				shapes.erase(shapes.begin() + i);
				i -= 1;
				glutPostRedisplay();
			}
		}
		selected = 0;
		break;
	case ']': //cycle selected primitive
		selected += 1;
		if (selected == shapes.size()) {
			selected = 0;
		}
		glutPostRedisplay();
		break;
	case '[':
		selected -= 1;
		if (selected == -1) {
			selected += shapes.size();
		}
		glutPostRedisplay();
		break;
	}
}

//display function, initiates canvas (initCanvas()) and then calls mainCanvas()
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	initCanvas();
	mainCanvas();
	glutSwapBuffers();
}

//main function, initialises GLUT and registers display and reshape functions, and input
//listeners
int main(int argc, char* argv[]) {
	helpConsole();
	// Initialize GLUT
	glutInit(&argc, argv);
	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// Set the window size
	glutInitWindowSize(500, 500);
	// Create the window with the title "2DCanvas"
	glutCreateWindow("2DCanvas");
	// Bind the functions to respond when necessary
	glutReshapeFunc(reshape);	//registers reshape function
	glutDisplayFunc(display);	//registers display function
	glutMouseFunc(mouseClick);	//registers mouseclick handler and listener
	glutSpecialFunc(specKeyPress);	//registers keypress handlers and listeners
	glutKeyboardFunc(normKeyPress);
	createGridMenu();			//registers grid on/off menu
	glutMainLoop();
	return 0;
}
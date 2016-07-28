/*
 * main.cpp
 * 
 * Rollercoaster Animation Features
 * 	+ File reader
 *  + BSpline drawer 
 *  - Animation player
 *  - Coaster model
 *  - Model loader
 *  - Background models
 *  - Rollercoaster rails
 * 
 */

#define _GLFW_X11
#define _GLFW_GLX
#define _GLFW_USE_OPENGL
#define _GLFW_HAS_GLXGETPROCADDRESS
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "Rollercoaster.h"
#include "FileReader.h"
#include "Frenetframe.h"
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <math.h>
#include <fstream>
#include <stdio.h>

using namespace std;

enum {NONE, ROTATE, ZOOM};

GLFWwindow* window;

// colors
GLfloat const WHITE[3] = {1.0f, 1.0f, 1.0f};
GLfloat const RED[3] = {1.0f, 0.0f, 0.0f};
GLfloat const GREEN[3] = {0.0f, 1.0f, 0.0f};
GLfloat const BLUE[3] = {0.0f, 0.0f, 1.0f};

// view variables
float const rotAngleScale   = 100.0f;
float const fov             = 60.0f;
float const nearPlane       = 1.0f;
float const farPlane        = 1000.0f;
int const width             = 1024;
int const height            = 768;

FileReader input;
Rollercoaster coaster;

// collections
vector<Vertex> points;
vector<Trackpoint> tracks;

vector<Vertex> leftPoints;
vector<Vertex> rightPoints;

vector<Trackpoint> leftTracks;
vector<Trackpoint> rightTracks;

// flags
bool playAnim = false;
bool showPoints = false;
bool showAxis = false;
bool showTracktype = false;
bool showTracks = false;

// general variables
Vertex lastPoint;
int   movement   = NONE;
int   order      = 3;
float zoom       = -30.0f;
float xRot       = 30.0f;
float zRot       = 0.0f;
float increment  = 0.0f;
float pointSize  = 10.0f;
float lineLength = 0.001f;

chrono::high_resolution_clock::time_point  lastTime;

float const chainVel  = 0.005f;
float u_value_start   = 0.99f;
float velocity        = 0.01f;
float u_value         = u_value_start;
Vertex currentPosition;
Trackpoint currentTrack;

// given cursor position get projected position
Vertex getTrackballPoint(double x, double y) {
    Vertex retVector;
    float d;

    retVector.setX(((2.0f * x) - width) / width);
    retVector.setY((height - (2.0f * y)) / height);
    retVector.setZ(0.0f);
    d = retVector.length();

    if(d >= 1.0f)
        d = 1.0f;

    retVector.setZ(sqrt(1.001 - (d * d)));
    retVector.normalize();

    return retVector;
}

// tracks mouse position
void mousePosFunc(GLFWwindow* win, double x, double y) {

    Vertex direction;
    Vertex currentPoint;
    Vertex rotAxis;
    double velocity, rotAngle;
    //GLfloat objectForm[16];

    if(movement == ROTATE) {

        printf("Rotating\n");
        currentPoint = getTrackballPoint(x, y);
        direction = currentPoint - lastPoint;
        velocity = direction.length();

        if(velocity > 0.0001) {
            rotAxis = Vertex::crossProduct(lastPoint, currentPoint);
            rotAngle = velocity * rotAngleScale;

            rotAxis.print();
            printf("Rotating by %f\n", rotAngle);

            glMatrixMode(GL_MODELVIEW);
            //glGetFloatv(GL_MODELVIEW_MATRIX, objectForm);
            glLoadIdentity();
            glRotatef(rotAngle, rotAxis.getX(), rotAxis.getY(), rotAxis.getZ());
            //glMultMatrixf(objectForm);
        }
    }
}

void mouseFunc(GLFWwindow* win, int button, int action, int mods) {
    
    double x, y;

    glfwGetCursorPos(window, &x, &y);

    if(action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
        movement = ROTATE;

        lastPoint = getTrackballPoint(x, y);

        printf("%f %f\n", x, y);

    }
    if(action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_LEFT) {
        movement = NONE;
    }

}

// Use mouse wheel to zoom
void scrollFunc(GLFWwindow* win, double x, double y) {

    zoom += y;
}

// keyboard input:
/*
* Enter: Toggles animation
* a key: displays axis
* c key: displays control points
* t key: displays colored tracks
* arrows: rotates camera
* space: displays attempt at tracks
*/
void keyboardFunc(GLFWwindow* win, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_ENTER:
                playAnim = !playAnim;
                lastTime = chrono::high_resolution_clock::now();
                u_value = u_value_start;
                break;
            case GLFW_KEY_A:
                showAxis = !showAxis;
                break;
            case GLFW_KEY_C:
                showPoints = !showPoints;
                break;
            case GLFW_KEY_M:
                increment += 0.1f;
                break;
            case GLFW_KEY_N:
                increment -= 0.1f;
                break;
            case GLFW_KEY_SPACE:
                showTracks = !showTracks;
                break;
            case GLFW_KEY_T:
                showTracktype = !showTracktype;
                break;
            case GLFW_KEY_LEFT:
                zRot -= 15.0f;
                break;
            case GLFW_KEY_RIGHT:
                zRot += 15.0f;
                break;
            case GLFW_KEY_UP:
                xRot += 15.0f;
                break;
            case GLFW_KEY_DOWN:
                xRot -= 15.0f;
                break;
            default:
                break;
        }
    }
}

// Shows axis
// Red is x-axis
// Green is y-axis
// Blue is z-axis
void viewAxis() {
    glBegin(GL_LINES);
        glColor3fv(RED);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);

        glColor3fv(GREEN);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);

        glColor3fv(BLUE);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();
}

double getVelocity(Tracktype t) {
    if(t == CHAIN) {
        return chainVel;
    }
    else if(t == FREE) {
        return 0.001f * sqrt(2 * 9.81f * (input.getHighest() - currentTrack.getY()));
    }
     else if(t == END) {
        return min(chainVel, velocity * 0.99f);
    }
    else {
        return chainVel;
    }
}

void setTrackColor(unsigned int i) {
  switch(tracks[i].getType()) {
  case FREE:
    glColor3fv(WHITE);
    break;
  case CHAIN:
    glColor3fv(GREEN);
    break;
  case END:
    glColor3fv(RED);
    break;
  }
}

// Ensures u is between 0 and 1
double wrapAroundCurve(double u) {
  if(u > 1.0f) {
    return u - 1.0f;
  }
  else {
    return 1.0f - u;
  }
}

void loadPoints(Rollercoaster c, Frenetframe *frame) {
    for(float i = 0.0f; i <= 1.0f; i += lineLength) {
        Vertex currentPoint = c.getPoint(i);
        Trackpoint currentTrack = c.getTrack(i);
        Vertex leftPoint, rightPoint;
        
        // loads second set of tracks
        if(showTracks) {
        
          *frame = Frenetframe::computeFrenet(c.getPoint(wrapAroundCurve(i - lineLength)), currentPoint, c.getPoint(wrapAroundCurve(i + lineLength)));
          
          leftPoint = frame->getBinormal() + currentPoint;
          rightPoint = (frame->getBinormal() * -1) + currentPoint;
        
          leftPoints.push_back(leftPoint);
          rightPoints.push_back(rightPoint);
          leftTracks.push_back(Trackpoint(currentTrack.getType(), leftPoint));
          rightTracks.push_back(Trackpoint(currentTrack.getType(), rightPoint));
        
        }
        // default track
        else {
          points.push_back(currentPoint);
          tracks.push_back(currentTrack);
        }
    }
}

void displaySpline(Rollercoaster c) {
    if (c.getPoints().size() > 1) {
      
        Frenetframe frame;

        // load points to draw
        loadPoints(c, &frame);

        // draw B-spline
        glBegin(GL_LINES);
              
              if(showTracks) {
              
                for (unsigned int i = 0; i < leftPoints.size()-1; i++) {
              
                  glVertex3f(leftPoints[i].getX(), leftPoints[i].getY(), leftPoints[i].getZ());
                  glVertex3f(leftPoints[i+1].getX(), leftPoints[i+1].getY(), leftPoints[i+1].getZ());
                  
                  glVertex3f(rightPoints[i].getX(), rightPoints[i].getY(), rightPoints[i].getZ());
                  glVertex3f(rightPoints[i+1].getX(), rightPoints[i+1].getY(), rightPoints[i+1].getZ());
                }
              }
              else {
                
                for(unsigned int i = 0; i < points.size() - 1; i++) {
                
                  if(showTracktype)
                    setTrackColor(i);
                
                  glVertex3f(points[i].getX(), points[i].getY(), points[i].getZ());
                  glVertex3f(points[i+1].getX(), points[i+1].getY(), points[i+1].getZ());
                }
              }
        glEnd();
    }
}

int main(int argc, char **argv)
{
	
  if(argc == 2) {
    input = FileReader(string(argv[1]));
    coaster = input.readCoaster();
    printf("%lu\n", coaster.getPoints().size());
  }
  else {
    printf("Please give a BSpline\n");
    exit(EXIT_FAILURE);
  }
	
	if(!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	
	window = glfwCreateWindow(width, height, "Rollercoaster Simulation CPSC 587", NULL, NULL);
	if(!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
    
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mousePosFunc);
    glfwSetMouseButtonCallback(window, mouseFunc);
    glfwSetKeyCallback(window, keyboardFunc);
    glfwSetScrollCallback(window, scrollFunc);

	while(!glfwWindowShouldClose(window)) {
		
    	glViewport(0, 0, width, height);
    	glClear(GL_COLOR_BUFFER_BIT);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(fov, width/height, nearPlane, farPlane);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, zoom);
        glRotatef(xRot, 1.0f, 0.0f, 0.0f);
        glRotatef(zRot, 0.0f, 1.0f, 0.0f);
        
        glColor3fv(WHITE);

        glPointSize(pointSize);

        // draw control points
        // ********************************************************
        if(showPoints) {
          glBegin(GL_POINTS);
              for (Controlpoint c : coaster.getPoints()) {
                glVertex3f(c.getX(), c.getY(), c.getZ());
              }
          glEnd();
        }


        //Draw dot/ coaster
        // ********************************************************
        glPointSize(20.0f);
        glColor3fv(RED);

        if(playAnim) {

            float time;
            float distance;

            currentTrack = coaster.getTrack(u_value);
            
            time = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - lastTime).count();
            time = time/100.0f;
            velocity = getVelocity(currentTrack.getType());
            distance = velocity * time;

            u_value -= distance;
            currentPosition = coaster.getPoint(u_value);

            glBegin(GL_POINTS);
                glVertex3f(currentPosition.getX(), currentPosition.getY(), currentPosition.getZ());
            glEnd();
            
            lastTime = chrono::high_resolution_clock::now();
            //printf("v(%f) * t(%f) = d(%f)\n", velocity, time, distance);
        }

        if(u_value < 0.0f || velocity <= 0.001f)
            u_value = u_value_start;

        if(showAxis)
            viewAxis();

        glColor3fv(WHITE);

        displaySpline(coaster);
            
        leftPoints.clear();
        rightPoints.clear();
        leftTracks.clear();
        rightTracks.clear();

        glfwSwapBuffers(window);
     	glfwPollEvents();

	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}

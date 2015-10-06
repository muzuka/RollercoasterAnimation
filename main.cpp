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
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <math.h>
#include <fstream>
#include <stdio.h>

using namespace std;

enum {NONE, ROTATE, ZOOM};

GLFWwindow* window;

GLfloat const RED[3] = {1.0f, 0.0f, 0.0f};
GLfloat const WHITE[3] = {1.0f, 1.0f, 1.0f};

float const rotAngleScale   = 100.0f;
float const fov             = 60.0f;
float const nearPlane       = 1.0f;
float const farPlane        = 1000.0f;
int const width             = 1024;
int const height            = 768;

FileReader input;
//BSpline coasterTrack;
Rollercoaster coaster;
vector<Vertex> points;
vector<Trackpoint> tracks;

bool playAnim = false;
bool showPoints = false;

Vertex lastPoint;
int   movement   = NONE;
int   order      = 3;
float zoom       = -30.0f;
float xRot       = 0.0f;
float zRot       = 0.0f;
float increment  = 0.0f;
float pointSize  = 10.0f;
float lineLength = 0.01f;

chrono::high_resolution_clock::time_point  lastTime;

float const chainVel  = 0.01f;
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

void scrollFunc(GLFWwindow* win, double x, double y) {

    zoom += y;
}

void keyboardFunc(GLFWwindow* win, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_ENTER:
                playAnim = true;
                lastTime = chrono::high_resolution_clock::now();
                u_value = u_value_start;
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

int main(int argc, char **argv)
{
	
  if(argc == 2) {
    input = FileReader(string(argv[1]));
    //coasterTrack = input.readBSpline();
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
        glRotatef(zRot, 0.0f, 0.0f, 1.0f);
        
        glColor3f(1.0f, 1.0f, 1.0f);

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
        glColor3f(1.0f, 0.0f, 0.0f);

        if(playAnim) {

            currentTrack = coaster.getTrack(u_value);
            //currentTrack.print();
            
            float time = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - lastTime).count();
            time = time/100.0f;

            if(currentTrack.getType() == CHAIN) {
                velocity = chainVel;
            }
            else if(currentTrack.getType() == FREE) {
                velocity = sqrt(2 * 9.81f * (input.getHighest() - currentTrack.getY()));
            }
            
            //velocity = 0.01f;

            float distance = velocity * time;

            printf("v(%f) * t(%f) = d(%f)\n", velocity, time, distance);

            u_value -= distance;

            currentPosition = coaster.getPoint(u_value);


            glBegin(GL_POINTS);
                glVertex3f(currentPosition.getX(), currentPosition.getY(), currentPosition.getZ());
            glEnd();
            
            lastTime = chrono::high_resolution_clock::now();
        }

        


        glColor3f(1.0f, 1.0f, 1.0f);

        if (coaster.getPoints().size() > 1) {

            // load points to draw
            for(float i = 0.0f; i <= 1.0f; i += lineLength) {
                points.push_back(coaster.getPoint(i));
                //tracks.push_back(coaster.getTrack(i));
            }

            // draw B-spline
            glBegin(GL_LINES);
                for (unsigned int i = 0; i < points.size(); i++) {
                    //if(tracks[i].getType() == FREE) {
                      //glColor3f(1.0f, 1.0f, 1.0f);
                    //}
                    //else if(tracks[i].getType() == CHAIN) {
                      //glColor3f(1.0f, 1.0f, 0.0f);
                    //}
                  
                    glVertex3f(points[i].getX(), points[i].getY(), points[i].getZ());
                    if (i != points.size() - 1) {
                        glVertex3f(points[i+1].getX(), points[i+1].getY(), points[i+1].getZ());
                    }
                }
            glEnd();
        }
            
        points.clear();

        glfwSwapBuffers(window);
     	glfwPollEvents();

	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}

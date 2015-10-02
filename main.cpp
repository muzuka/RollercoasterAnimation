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

#include "BSpline.h"
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

float const rotAngleScale   = 100.0f;
float const fov             = 60.0f;
float const nearPlane       = 1.0f;
float const farPlane        = 1000.0f;
int const width             = 1024;
int const height            = 768;

FileReader input;
BSpline coasterTrack;
vector<Vertex> points;

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

float velocity   = 0.01f;
float u_value    = 1.0f;
Vertex position;

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
    GLfloat objectForm[16];

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
                u_value = 1.0f;
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
    coasterTrack = input.readBSpline();
    printf("%lu\n", coasterTrack.getPoints().size());
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
    
    lastTime = chrono::high_resolution_clock::now();
    
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
          for (controlPoint c : coasterTrack.getPoints()) {
            glVertex3f(c.getX(), c.getY(), c.getZ());
          }
      glEnd();
    }


    //Draw dot/ coaster
    // ********************************************************
    glPointSize(20.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    if(playAnim) {
        
        float time = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - lastTime).count();
        time = time/100.0f;
        float distance = velocity * time;

        //printf("v(%f) * t(%f) = d(%f)\n", velocity, time, distance);

        u_value -= distance;

        position = coasterTrack.getPoint(u_value);

        glBegin(GL_POINTS);
            glVertex3f(position.getX(), position.getY(), position.getZ());
        glEnd();
        
        lastTime = chrono::high_resolution_clock::now();
    }

    


    glColor3f(1.0f, 1.0f, 1.0f);

    if (coasterTrack.getPoints().size() > 1) {

        // load points to draw
        for(float i = 0.0f; i <= 1.0f; i += lineLength) {
            points.push_back(coasterTrack.getPoint(i));
        }

        // draw B-spline
        glBegin(GL_LINES);
            for (int i = 0; i < points.size(); i++) {
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

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
#include <math.h>
#include <fstream>
#include <stdio.h>

using namespace std;

GLFWwindow* window;

float const fov = 60.0f;
float const nearPlane = 1.0f;
float const farPlane = 1000.0f;
int const width = 1024;
int const height = 768;

FileReader input;
BSpline coasterTrack;
vector<Vertex> points;

bool  showPoints = false;
int   order      = 3;
float rotAngle   = 0.0f;
float increment  = 0.0f;
float pointSize  = 10.0f;
float lineLength = 0.01f;

void keyboardFunc(GLFWwindow* win, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_C:
                showPoints = !showPoints;
                break;
            case GLFW_KEY_LEFT:
                rotAngle -= 15.0f;
                break;
            case GLFW_KEY_RIGHT:
                rotAngle += 15.0f;
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
	
	glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyboardFunc);
    glPointSize(pointSize);
	
	while(!glfwWindowShouldClose(window)) {
		
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, width/height, nearPlane, farPlane);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(rotAngle, 0.0f, 1.0f, 0.0f);
    
    glColor3f(1.0f, 1.0f, 1.0f);

    if(showPoints) {
      glBegin(GL_POINTS);
          for (controlPoint c : coasterTrack.getPoints()) {
            glVertex3f(c.getX(), c.getY(), c.getZ());
          }
      glEnd();
    }

    if (coasterTrack.getPoints().size() > 1) {
        for(float i = 0.0f; i <= 1.0f; i += lineLength) {
            bool draw;
            if(increment == i) {
                draw = true;
            }
            else {
                draw = false;
            }
            points.push_back(coasterTrack.getPoint(i, draw));
        }

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

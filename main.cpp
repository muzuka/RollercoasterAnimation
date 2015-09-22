/*
 * main.cpp
 * 
 * 
 */

#define _GLFW_X11
#define _GLFW_GLX
#define _GLFW_USE_OPENGL
#define _GLFW_HAS_GLXGETPROCADDRESS
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

GLFWwindow* window;

float const fov = 60.0f;
float const nearPlane = 1.0f;
float const farPlane = 1000.0f;
int const width = 1024;
int const height = 768;

FileReader in;
BSpline coasterTrack;

int main(int argc, char **argv)
{
	
	if(argc == 2) {
    in(string(argv[1]));
    coasterTrack = in.readBSpline();
	}
  else {
    printf("Please give a BSpline\n");
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

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, width/height, nearPlane, farPlane);
	
	while(!glfwWindowShouldClose(window)) {
		
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		

		glfwSwapBuffers(window);
 		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}

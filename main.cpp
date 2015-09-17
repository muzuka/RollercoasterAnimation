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

int const width = 1024;
int const height = 768;

int main(int argc, char **argv)
{
	
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	
	window = new GLFWCreateWindow(width, height, "Rollercoaster Simulation CPSC 587", NULL, NULL);
	if(!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	return 0;
}


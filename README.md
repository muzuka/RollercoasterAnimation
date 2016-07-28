# RollercoasterAnimation
A B-spline based rollercoaster animation using OpenGL and GLFW.

## Controls:

### Essential controls
* Enter key -> Starts the animation
* Arrow keys -> Rotates the track

### Debug controls
* C key -> Shows control points
* T key -> Shows track type (normal, chain, brakes)
* A key -> Shows axis

## Getting Started

These instructions will help with running the program.

Use this as the base compile instruction

~~~
g++ -o main main.cpp BSpline.cpp Controlpoint.cpp FileReader.cpp Frenetframe.cpp KnotSequence.cpp Rollercoaster.cpp Trackpoint.cpp Vertex.cpp -std=c++0x
~~~

OpenGL has platform specific flags so try these anywhere around "-o main" and after g++.

For Mac:
~~~
-framework Opengl
~~~

For Linux:
~~~
-lGL
~~~

For Windows:
~~~
-lopengl32
~~~

You will need GLFW installed to run this program.
Just add the following if you have GLFW installed.
~~~
-lglfw3
~~~

## Track loading

This project stores tracks in text files and loads them in the command line.
When executing the program just include the path to the desired track.

I created a script for Blender that outputs a selected curve called CurveOutput.py.
This allows you to create tracks in blender and use them in the program.

You do have to enter tracktypes manually though. If there are none it will default to normal track.
e = end track which applies brakes.
f = normal track
c = chain track which sets car to a constant velocity

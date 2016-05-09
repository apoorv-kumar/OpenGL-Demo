Please see the license (BSD 2) at the bottom.

##Open GL Projects - 2012
Basic OpenGL projects that I have worked on for graphics course. These include voxel based scene generations. Projection / hidden surface implementations from the scratch.

###voxel scene
	This is an animation scene
	Renders:
	1. A HOUSE
	2. A TREE
	3. A WELL
	4. PATHWAY TO HOUSE
	using voxels (cubes)
	To be able to visualize the scene properly
	the cube have separate colored edges (shaded green/red/blue)

	------------------------------------------------------------------------------------------
	Instructions to compile on linux:

	Dependencies - library glut and library GLU

	1. run - 
	g++ -lglut -lGLU anim.cpp

	2. this would create an 'a.out' executable
	------------------------------------------------------------------------------------------


	-----------------------------------------------------------------------------------------
	Usage instructions:

	Execute the executable
	./a.out

	The scene is rendered on screen
	The scene auto rotates to give a 3D view
	------------------------------------------------------------------------------------------


	------------------------------------------------------------------------------------------
	Controls:
	Not required
	------------------------------------------------------------------------------------------


###transformation


	This is an animation scene , created solely out of transformed cubes.
	Tansformations include - rotation , shear, translation and ofcourse scaling.
	It depicts 1 house , 1 tree , and 2 men walking at different speeds.

	------------------------------------------------------------------------------------------
	Instructions to compile on linux:

	Dependencies - library glut and library GLU

	1. run - 
	g++ -lglut -lGLU anim.cpp

	2. this would create an 'a.out' executable
	------------------------------------------------------------------------------------------


	-----------------------------------------------------------------------------------------
	Usage instructions:

	Execute the executable
	./a.out

	Sit back and enjoy
	------------------------------------------------------------------------------------------


	------------------------------------------------------------------------------------------
	Controls:
	Not required
	------------------------------------------------------------------------------------------



###matrix
	This sort of a library code of matrix operations within the umbrella class - Transformations

	------------------------------------------------------------------------------------------
	Instructions to compile on linux:

	Dependencies - stl

	1. run - 
	g++ matrix.cpp

	2. this would create an 'a.out' executable
	------------------------------------------------------------------------------------------


	------------------------------------------------------------------------------------------
	Features:

	There are functions for the following transformations:
	1. translate list of points
	2. scale list of points
	3. rotate list about x , y or z
	------------------------------------------------------------------------------------------


	-----------------------------------------------------------------------------------------
	Usage instructions:

	Insert values into main() function

	Compile the code

	Execute the executable
	./a.out

	------------------------------------------------------------------------------------------


###Cube Blocks Animation

	This is an animation of a cuboid made of 3 distinct cubes stacked upon one another 
	travelling through a 3x3 framework made out of 8 cubes , with a hole at center.


	------------------------------------------------------------------------------------------
	Instructions to compile on linux:

	Dependencies - library glut and library GLU

	1. run - 
	g++ -lglut -lGLU anim.cpp

	2. this would create an 'a.out' executable
	------------------------------------------------------------------------------------------


	-----------------------------------------------------------------------------------------
	Usage instructions:

	Execute the executable
	./a.out

	The cuboid stops after each cube (it consists of) moves through the 3x3 frame.
	------------------------------------------------------------------------------------------


	------------------------------------------------------------------------------------------
	Controls:
	Press <SPACE> to mobilize a stopped cube. (and do so every time it stops)

	Use 'U' and 'D' keys for rotating the setup up and down (to create different viewing angles)

	Use 'R' and 'L' keys for rotating left or right.

	Use 'X' and 'Z' keys for rotating about X and Z axes.

	Press 'Esc' to quit the animation
	------------------------------------------------------------------------------------------


------------------------------------------------------------------------------------------
Copyright (c) <2012>, <Apoorv Kumar>
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are 
permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of 
conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list 
of conditions and the following disclaimer in the documentation and/or other materials
 provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
------------------------------------------------------------------------------------------


//============================================================================
// Name        : GraphicsHw2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include <vector>
#include <string>
#include "./objects/Object.h"
#include "./objects/Cube.h"
#include "./objects/Character.h"
#include "./objects/LightObject.h"

using namespace std;

Character *player;
	//static vector<Cube*> cubes;
	int grid_size=64;
	LightObject sun;
	vector<Cube*> cubes;
	float sizeOfCube=0.5;
	//METHODS
GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };


void createField(){
	//cubes.push_back(new Cube(sizeOfCube,0,0,0));
	for(int i=0;i<grid_size;i++){
		for(int j=0;j<grid_size;j++){
				cubes.push_back(new Cube(sizeOfCube,-i*(sizeOfCube+0.01),0,-j*sizeOfCube));
				cubes.push_back(new Cube(sizeOfCube,i*(sizeOfCube+0.01),0,-j*sizeOfCube));
		}
	}

}

void reshapeScene(int w,int h){

		// Prevent a divide by zero, when window is too short
		// (you cant make a window of zero width).
		if(h == 0)
			h = 1;
		float ratio = 1.0* w / h;

		// Use the Projection Matrix
		glMatrixMode(GL_PROJECTION);

			// Reset Matrix
		glLoadIdentity();

		// Set the viewport to be the entire window
		glViewport(0, 0, w, h);

		// Set the correct perspective.
		gluPerspective(45,ratio,1,1000);

		// Get Back to the Modelview
		glMatrixMode(GL_MODELVIEW);
	}

	void renderScene(){
		//Clear Color and Depth Buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Reset transformations
		glLoadIdentity();

		// Set the camera
		gluLookAt(	0, 1.0f, 1,
					0,1,0,
					0.0f, 1.0f,  0.0f);

	        // Draw ground

		int i;
		int j;

		for (vector<Cube*>::iterator it = cubes.begin() ; it != cubes.end(); ++it){
			(*it)->view();
		}
		cout << cubes.size() << endl;
		//glTranslatef(0.0,0.0,sizeOfCube1);
		//drawCube(sizeOfCube);
		/*glTranslatef(-3.2f, 0.0f, 0.0f);
		glColor3f(1.0,1.0,1.0);
		glutWireCube(sizeOfCubef);
		glTranslatef(sizeOfCubef, 0.0f, 0.0f);
		glutWireCube(sizeOfCubef);*/


		glutSwapBuffers();
	}
	void init(int argc,char** argv){
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(100, 100);
		glutInitWindowSize(500, 500);
		glutCreateWindow("Something Like Minecraft");
		createField();

		glutDisplayFunc(renderScene);
		glutReshapeFunc(reshapeScene);
		// OpenGL init
		glEnable(GL_DEPTH_TEST);
		glutMainLoop();

	}

int main(int argc,char** argv) {
	init(argc,argv);

	return EXIT_SUCCESS;
}

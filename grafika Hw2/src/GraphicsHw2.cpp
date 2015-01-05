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
#include <math.h>
#include "./objects/Object.h"
#include "./objects/Cube.h"
#include "./objects/Character.h"
#include "./objects/LightObject.h"

using namespace std;

	Character *player;
	int grid_size=64;
	LightObject sun;
	vector<Cube*> cubes;
	float sizeOfCube=0.5;

	// angle of rotation for the camera direction
	float angle = 0.0f;

	// actual vector representing the camera's direction
	float lx=0.0f,lz=-1.0f;

	// XZ position of the camera
	float x=0.0f, z=5.0f;

	// the key states. These variables will be zero
	//when no key is being presses
	float deltaAngle = 0.0f;
	float deltaMove = 0;
	int xOrigin = -1;

	void computePos(float deltaMove) {

		x += deltaMove * lx * 0.1f;
		z += deltaMove * lz * 0.1f;
	}

	void processNormalKeys(unsigned char key, int xx, int yy) {

	        if (key == 27)
	              exit(0);
	}

	void pressKey(int key, int xx, int yy) {

	       switch (key) {
	             case GLUT_KEY_UP : deltaMove = 0.5f; break;
	             case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
	       }
	}

	void releaseKey(int key, int x, int y) {

	        switch (key) {
	             case GLUT_KEY_UP :
	             case GLUT_KEY_DOWN : deltaMove = 0;break;
	        }
	}

	void mouseMove(int x, int y) {

		// this will only be true when the left button is down
		if (xOrigin >= 0) {

			// update deltaAngle
			deltaAngle = (x - xOrigin) * 0.001f;

			// update camera's direction
			lx = sin(angle + deltaAngle);
			lz = -cos(angle + deltaAngle);
			//Redisplay or glRotafef() the panel
			cout << lx << lz << endl;
			//glutPostRedisplay();
		}
	}

	void mouseButton(int button, int state, int x, int y) {

		// only start motion if the left button is pressed
		if (button == GLUT_LEFT_BUTTON) {

			// when the button is released
			if (state == GLUT_UP) {
				angle += deltaAngle;
				xOrigin = -1;
			}
			else  {// state = GLUT_DOWN
				xOrigin = x;
			}
		}
	}

	void createField(){
		//cubes.push_back(new Cube(sizeOfCube,0,0,0));
		for(int i=0;i<grid_size;i++){
			for(int j=0;j<grid_size;j++){
					cubes.push_back(new Cube(sizeOfCube,-i*(sizeOfCube+0.01),0,-j*sizeOfCube));
					//cubes.push_back(new Cube(sizeOfCube,i*(sizeOfCube+0.01),0,-j*sizeOfCube));
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

		if (deltaMove)
				computePos(deltaMove);

		//Clear Color and Depth Buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Reset transformations
		glLoadIdentity();

		// Set the camera
		gluLookAt(	x, 1.0f, z,
				x+lx, 1.0f,  z+lz,
				0.0f, 1.0f,  0.0f);

		// Draw the GROUND
		for (vector<Cube*>::iterator it = cubes.begin() ; it != cubes.end(); ++it){
			(*it)->view();
		}
		cout << cubes.size() << endl;


		glutSwapBuffers();
	}

	void init(int argc,char** argv){
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(100, 100);
		glutInitWindowSize(500, 500);
		glutCreateWindow("Something Like Minecraft");
		createField();
		//Mouse LIsteners
		glutMouseFunc(mouseButton);
		glutMotionFunc(mouseMove);
		glutIgnoreKeyRepeat(1);
		glutKeyboardFunc(processNormalKeys);
		glutSpecialFunc(pressKey);
		glutSpecialUpFunc(releaseKey);

		glutDisplayFunc(renderScene);
		glutReshapeFunc(reshapeScene);
		//redraw continuously
		glutIdleFunc(renderScene);

		// OpenGL init
		glEnable(GL_DEPTH_TEST);
		glutMainLoop();

	}

	int main(int argc,char** argv) {
		init(argc,argv);

		return EXIT_SUCCESS;
	}

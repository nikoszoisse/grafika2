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
#include "./objects/settings.h"
#include "./objects/Object.h"
#include "./objects/Cube.h"
#include "./objects/Character.h"
#include "./objects/LightObject.h"
#include "./objects/Sun.h"
#include "./objects/Token.h"

using namespace std;

	Character *player = new Character(start_x, start_y, start_z);
	Sun *sun = new Sun(sun_start_x, sun_start_y, sun_start_z, sun_size_rad);

	vector<Cube*> cubes[grid_size];
	vector<Token*> tokens;

	bool sun_to_view = true;


	// the key states. These variables will be zero
	//when no key is being presses
	float xdeltaAngle = 0.0f;
	float ydeltaAngle = 0.0f;
	int xOrigin = -1;
	int yOrigin = -1;


	// actual vector representing the camera's direction
	float lx=0.0f,ly=0.0f,lz=1.0f;
	//Camera's Eye Position
	float x_cam = start_x+lx,
			y_cam = start_y+ly,
			z_cam = start_z+lz; // se it like 3rd person
	// angle of rotation for the camera direction
	float xangle = 0.0f;
	float yangle = 0.0f;

	void processNormalKeys(unsigned char key, int xx, int yy) {

	        if (key == 27)
	              exit(0);
	}

	void pressKey(unsigned char key, int xx, int yy) {

	       switch (key) {
	             case 'w' : player->moveForward(); break;
	             case 's' : player->moveBackWard(); break;
	             case 'a' : player->moveLeft(); break;
	             case 'd' : player->moveRight(); break;
	             //TODO remove z, is for testing light Position
	             case 'z' : sun->setPosition(1.0f,3.0f,130.0f);break;
	             case 'x' : sun->setPosition(1.0f,1.0f,65.0f);break;
	             //Hide the sun
	             case 'c' : sun_to_view = !sun_to_view;sun->hide();break;
	             case 'l' : tokens.push_back(new Token(player->getXPos(),player->getYPos()+1,player->getZPos(),0.3));break;
	       }
          // glutPostRedisplay();
	}

	void releaseKey(unsigned char key, int xx, int yy) {

	        switch (key) {
	             case 'w' :
	             case 's' : break;
	             case 'a' :
	             case 'd' : break;
	        }
	}

	void mouseMove(int mx, int my) {

		// this will only be true when the middle button is down
		if(xOrigin>=0 || yOrigin>=0){
			// update deltaAngle
			xdeltaAngle = (mx - xOrigin) * 0.001f;
			ydeltaAngle = (my- yOrigin) * 0.001f;

			// update camera's direction  (EYE) looks at camera center point
			lx = sin(xangle + xdeltaAngle);
			ly = sin(yangle + ydeltaAngle);
			lz = cos(xangle + xdeltaAngle);
			//glutPostRedisplay();
		}
	}

	void mouseButton(int button, int state, int mx, int my) {
		//TODO REMOVE LEFT
		if(button == GLUT_MIDDLE_BUTTON || button == GLUT_LEFT){
			if(state == GLUT_UP){
			xangle += xdeltaAngle;
			yangle += ydeltaAngle;
			yOrigin = -1;
			xOrigin = -1;
			}
			else{
				xOrigin = mx;
				yOrigin = my;
			}
		}
	}

	void createField(){
		bool center=false;
		for(int i=0;i<=grid_size;i++){
					for(int j=0;j<=grid_size;j++){
						Cube* tmp;
						if((i==grid_size/2&&j==grid_size/2))
							center = true;
						else
							center = false;

						tmp = new Cube(sizeOfCube,i*(sizeOfCube+gap_size),0,j*(sizeOfCube+gap_size),center);
						tmp->setRandomColor();
						cubes[grid_floor].push_back(tmp);
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
		x_cam = player->getXPos();
		y_cam = player->getYPos();
		z_cam = player->getZPos();

		gluLookAt(	x_cam, y_cam+2, z_cam-2,
				x_cam+lx, y_cam+ly,  z_cam+lz,
				0.0f, 1.0f,  0.0f);

		if(sun_to_view){
			sun->view();
		}
		//PLAyer view
		player->view();

		// Draw the TOkens
		for (vector<Token*>::iterator it = tokens.begin() ; it != tokens.end(); ++it){
			(*it)->view();
		}

		// Draw the GROUND
		for (vector<Cube*>::iterator it = cubes[grid_floor].begin() ; it != cubes[grid_floor].end(); ++it){
			(*it)->view();
		}


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
		glutKeyboardFunc(pressKey);
		glutKeyboardUpFunc(releaseKey);
		//glutSpecialFunc(pressKey);
		//glutSpecialUpFunc(releaseKey);

		// OpenGL init
		glEnable(GL_DEPTH_TEST);
	    glShadeModel(GL_SMOOTH);

	    // Renormalize scaled normals so that lighting still works properly.
	    glEnable( GL_NORMALIZE);

		// Specify a global ambient
		GLfloat globalAmbient[] = { 0.2, 0.2, 0.2, 1.0 };
		//glLightModelfv( GL_LIGHT_MODEL_AMBIENT, globalAmbient );
		glEnable(GL_LIGHTING);

		glutDisplayFunc(renderScene);
		glutReshapeFunc(reshapeScene);
		//redraw continuously
		glutIdleFunc(renderScene);

		glutMainLoop();

	}

	int main(int argc,char** argv) {
		init(argc,argv);

		return EXIT_SUCCESS;
	}

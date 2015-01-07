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
#include "./objects/Sun.h"
#include "./objects/Token.h"

#define grid_size 64

using namespace std;

	//Character *player;
	Sun *sun = new Sun(1,1,65,3);

	vector<Cube*> cubes;
	vector<Token*> tokens;
	float sizeOfCube=1;

	// angle of rotation for the camera direction
	float xangle = 0.0f;
	float yangle = 0.0f;
	bool sun_to_view = false;
	// actual vector representing the camera's direction
	//float lx=0.0f,lz=-1.0f;
	float lx=0.0f,ly=0.0f,lz=1.0f;

	// XZ position of the camera
	//float x=-16.5f, z=-14.5f;
	float x=32.0f, y=1.0f, z=32.0f;

	// the key states. These variables will be zero
	//when no key is being presses
	float xdeltaAngle = 0.0f;
	float ydeltaAngle = 0.0f;
	float fwd_deltaMove = 0;
	float side_deltaMove = 0;
	int xOrigin = -1;
	int yOrigin = -1;

	void computePos() {
		/*These VAlues depended from camera, we dont
		x += deltaMove * lx * 0.1f;
		z += deltaMove * lz * 0.1f;
		*/
		x += side_deltaMove * 0.3f;
		z += fwd_deltaMove * 0.3f;
	}

	void processNormalKeys(unsigned char key, int xx, int yy) {

	        if (key == 27)
	              exit(0);
	}

	void pressKey(unsigned char key, int xx, int yy) {

	       switch (key) {
	             case 'w' : fwd_deltaMove = 0.5f; break;
	             case 's' : fwd_deltaMove = -0.5f; break;
	             case 'a' : side_deltaMove = 0.5f; break;
	             case 'd' : side_deltaMove = -0.5f; break;
	             //TODO remove z, is for testing light Position
	             case 'z' : sun->setPosition(1.0f,64.0f,65.0f);break;
	             case 'x' : sun->setPosition(1.0f,1.0f,65.0f);break;
	             //Hide the sun
	             case 'c' : sun_to_view = !sun_to_view;sun->hide();break;
	             case 'v' : x = 0.0f;z=0.0f;break;
	             case 'l' : cout << x<<", "<<z<<endl;tokens.push_back(new Token(x+lx,2,z+lz,0.3));break;
	       }
	}

	void releaseKey(unsigned char key, int xx, int yy) {

	        switch (key) {
	             case 'w' :
	             case 's' : fwd_deltaMove = 0.0f;break;
	             case 'a' :
	             case 'd' : side_deltaMove = 0.0f;break;
	        }
	}

	void mouseMove(int mx, int my) {

		// this will only be true when the left button is down
		if (xOrigin >= 0) {

			// update deltaAngle
			xdeltaAngle = (mx - xOrigin) * 0.001f;
			ydeltaAngle = (my- yOrigin) * 0.001f;

			// update camera's direction  (EYE)
			lx = sin(xangle + xdeltaAngle);
			ly = sin(yangle + ydeltaAngle);
			lz = -cos(xangle + xdeltaAngle);

			cout << x <<", "<< z <<endl;
		}
	}

	void mouseButton(int button, int state, int mx, int my) {

		// only start motion if the left button is pressed
		if (button == GLUT_LEFT_BUTTON) {

			// when the button is released
			if (state == GLUT_UP) {
				xangle += xdeltaAngle;
				xOrigin = -1.0f;
				yangle += ydeltaAngle;
				yOrigin = -1.0f;
			}
			else  {// state = GLUT_DOWN
				xOrigin = mx;
				yOrigin = my;
			}
		}
	}

	void createField(){
		bool center=false;
		/*for(int i=0;i<grid_size;i++){
			for(int j=0;j<grid_size;j++){
				if(i==grid_size/2&&j==grid_size/2){
					center=true;
					cubes.push_back(new Cube(sizeOfCube,-i*(sizeOfCube+0.01),0,-j*sizeOfCube,center));
				}
				else{
					center=false;
					cubes.push_back(new Cube(sizeOfCube,-i*(sizeOfCube+0.01),0,-j*sizeOfCube,center));
				}
			}
		}*/

		for(int i=0;i<=grid_size;i++){
					for(int j=0;j<=grid_size;j++){
						if(i==grid_size/2&&j==grid_size/2){
							center=true;
							cubes.push_back(new Cube(sizeOfCube,i*(sizeOfCube+0.01),0,j*(sizeOfCube+0.01),center));
						}
						else{
							center=false;
							cubes.push_back(new Cube(sizeOfCube,i*(sizeOfCube+0.01),0,j*sizeOfCube,center));
						}
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
		if (fwd_deltaMove || side_deltaMove){
				computePos();
		}

		//Clear Color and Depth Buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Reset transformations
		glLoadIdentity();
		glTranslatef(.0, .0, -5);
		// Set the camera
		gluLookAt(	x, y, z,
				x+lx, y+ly,  z+lz,
				0.0f, 1.0f,  0.0f);
		if(sun_to_view){
			sun->view();
		}
		/*//TODO remove them Is for Testing
		glLineWidth(5);
		//X
		glBegin(GL_LINES);
			glColor4f(255,0,0,1.0);
		  glVertex3f(-32.0f, 0.0f, 0.0f);
		  glVertex3f(32.0f, 1.0f, 0.0f);
		glEnd();
		//Y
		glBegin(GL_LINES);
			glColor4f(0,255,0,1.0);
		  glVertex3f(0.0f, -32.0f, 0.0f);
		  glVertex3f(0.0f, 32.0f, 0.0f);
		glEnd();
		//Z
		glBegin(GL_LINES);
			glColor4f(0,0,255,1.0);
		  glVertex3f(0.0f, 0.0f, -32.0f);
		  glVertex3f(0.0f, 0.0f, 32.0f);
		glEnd();*/

		// Draw the TOkens
		for (vector<Token*>::iterator it = tokens.begin() ; it != tokens.end(); ++it){
			(*it)->view();
		}

		// Draw the GROUND
		for (vector<Cube*>::iterator it = cubes.begin() ; it != cubes.end(); ++it){
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

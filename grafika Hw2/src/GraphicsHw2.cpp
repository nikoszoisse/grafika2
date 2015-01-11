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
	float x_eye = start_x+lx,
			y_eye = start_y+ly,
			z_eye = start_z+lz; // se it like 3rd person
	float x_center = x_eye,
			y_center = y_eye,
			z_center = z_eye;
	// angle of rotation for the camera direction
	float xangle = 0.0f;
	float yangle = 0.0f;

	int v_Key_pressed_times = 0;

	/*void checkIfHeClimbs(string collusion,bool collision){
		int player_y=player->getYPos();
		float player_z=player->getZPos();
		float player_x=player->getXPos();
		bool climbed=false;
		if(cubes[player_y+1].empty()&&collision){
			player->setPosition(player_x,player_y+1,
				player_z);
			climbed=true;
		}
	}*/

	void setCube(){
		Cube* cube;
		int pos=player->getYPos();
		int dir_x=player->getDir_x();
		int dir_z=player->getDir_z();
		cout << dir_x << " "<<dir_z <<endl;
		if(dir_x){
			cube=new Cube(sizeOfCube,player->getXPos()+dir_x*1,
					player->getYPos(),player->getZPos(),false);
		}
		else if(dir_z){
			cube=new Cube(sizeOfCube,player->getXPos(),
					player->getYPos(),player->getZPos()+dir_z*1,false);
		}
		if(cube!=NULL){
			cube->setRandomColor();
			cubes[pos].push_back(cube);
		}

	}
	void hasCollusion(string collusion){
			int player_y = player->getYPos();
			bool collision=false;
			for (vector<Cube*>::iterator it = cubes[player_y].begin() ; it != cubes[player_y].end(); ++it){
				if(player->hasCollision(*it)){
						collision=true;
						player->stopMoving();
				}
			}
			//checkIfHeClimbs(collusion,collision);

			/*Out of Bundaries*/
			if(player->getXPos()>=65||player->getYPos()>=65||
					player->getZPos()>=65){
				player->stopMoving();
				player->setPosition(start_x,start_y,start_z);
			}
	}

	void handleCameraView(){
		if(v_Key_pressed_times%5 == 0){
			v_Key_pressed_times = 0;
			// Set the camera
			x_eye = player->getXPos();
			y_eye = player->getYPos()+2;
			z_eye = player->getZPos()-2;

			x_center = x_eye;
			y_center = y_eye-1;
			z_center = z_eye;
		}else{
			x_center = grid_size/2;
			y_center = 1;
			z_center = grid_size/2;
		}

		if(v_Key_pressed_times == 1){
			x_eye = 1;
			y_eye = grid_size/2+1;
			z_eye = 1;
		}
		else if(v_Key_pressed_times == 2){
			x_eye = 1;
			y_eye = grid_size/2+1;
			z_eye = grid_size;
		}else if(v_Key_pressed_times == 3){
			x_eye = grid_size;
			y_eye = grid_size/2+1;
			z_eye = 1;
		}else if(v_Key_pressed_times == 4){
			x_eye = grid_size;
			y_eye = grid_size/2+1;
			z_eye = grid_size;
		}
	}

	void processNormalKeys(unsigned char key, int xx, int yy) {

	        if (key == 27)
	              exit(0);
	}

	void pressKey(unsigned char key, int xx, int yy) {

	       switch (key) {
	             case 'w' : player->moveForward();hasCollusion("z"); break;
	             case 's' : player->moveBackWard();player->moveForward();hasCollusion("z");break;
	             case 'a' : player->moveLeft(); player->moveForward(); hasCollusion("z");break;
	             case 'd' : player->moveRight(); player->moveForward();hasCollusion("z");break;
	             case 'v' : v_Key_pressed_times++;break;
	             //TODO remove z, is for testing light Position
	             case 'z' : sun->setPosition(1.0f,3.0f,130.0f);break;
	             case 'x' : sun->setPosition(1.0f,1.0f,65.0f);break;
	             //Hide the sun
	             case 'c' : sun_to_view = !sun_to_view;sun->hide();break;
	             case 'l' : tokens.push_back(new Token(player->getXPos(),
	            		 player->getYPos(),player->getZPos(),token_size_rad));break;
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
		if(button == GLUT_MIDDLE_BUTTON){
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
		else if(button==GLUT_LEFT_BUTTON){
			setCube();
		}
	}

	void createField(){
		bool center=false;
		for(int i=0;i<=grid_size;i++){
					for(int j=0;j<=grid_size;j++){
						Cube* tmp;
						if((i==grid_size/2&&j==grid_size/2)){
							tmp = new Cube(sizeOfCube,i*(sizeOfCube+gap_size),1,(j+1)*(sizeOfCube+gap_size),center);
							tmp->setRandomColor();
							cubes[1].push_back(tmp);
							center = true;
						}
						else{
							center = false;
						}

						tmp = new Cube(sizeOfCube,i*(sizeOfCube+gap_size),0,j*(sizeOfCube+gap_size),center);
						//tmp = new Cube(sizeOfCube,(i+gap_size)*sizeOfCube,0,(j+gap_size)*sizeOfCube,center);
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

		//Set Camera
		handleCameraView();
		gluLookAt(	x_eye, y_eye, z_eye,
				x_center+lx, y_center+ly,  z_center+lz,
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
		// Draw the GROUND
		for (vector<Cube*>::iterator it = cubes[1].begin() ; it != cubes[1].end(); ++it){
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

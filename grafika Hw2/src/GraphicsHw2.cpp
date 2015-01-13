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
#include <sstream>
#include <math.h>
#include "./objects/settings.h"
#include "./objects/Object.h"
#include "./objects/Cube.h"
#include "./objects/Character.h"
#include "./objects/LightObject.h"
#include "./objects/Sun.h"
#include "./objects/Token.h"

using namespace std;
	Character *player = new Character(start_x,start_y,start_z);//start_x*(sizeOfCube+gap_size), start_y, start_z*(sizeOfCube+gap_size));
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
	bool show_apothema = false;


	void delete_Cube(Cube* match){
		for(int floor=grid_floor;floor<grid_size;floor++){
			for (vector<Cube*>::iterator it = cubes[floor].begin();
					it != cubes[floor].end(); ++it){
				if((*it)->ID == match->ID&&!(*it)->isCenter()){
					cubes[floor].erase(it);
					return;
				}
			}
		}
	}


	void checkIfHeClimbs(){
		float player_y=player->getYPos();
		float player_z=player->getZPos();
		float player_x=player->getXPos();
		Cube *col_cube;
		if(col_cube==hasCollusion(player,"z")){
			Cube *upside_cube;
			col_cube->setDirection(new double[3]{0,1,0})
			if(upside_cube==hasCollusion(col_cube,"y")==NULL){
				player->setPosition(player_x,player_y+1,player_z);
				player->points+=5;
			}

		}
	}

	Cube* hasCollusion(Object* obj,string collusion){
			int obj_floor;
			if(collusion == "z")
				obj_floor= obj->getYPos();
			else if(collusion == "y"){
				obj_floor = obj->getYPos() + 1*obj->getDir_y();
				cout << "obj to seek"<<obj_floor<<endl;
				if(obj_floor < grid_floor)
					return false;
			}

			for (vector<Cube*>::iterator it = cubes[obj_floor].begin() ; it != cubes[obj_floor].end(); ++it){
				if(obj->hasCollision(*it)){
						//checkIfHeClimbs();
						obj->stopMoving();
						return (*it);
				}
			}
			return NULL;
	}
	/*Ερωτημα viii*/
	void collapse(){
		bool there_is_collapse=false;
		for(int floor=grid_size-1;floor!=0;floor--){
			for (vector<Cube*>::iterator it = cubes[floor].begin();
					it != cubes[floor].end(); ++it){

				Cube * col_cube;

				(*it)->moveDown();
				col_cube = hasCollusion((*it),"y");
				if(!col_cube){
					cubes[floor-1].push_back((*it));
					if((int)(*it)->getYPos()<=0){
						there_is_collapse=true;
						(*it)->moveDown();
					}
				}
			}
		}

		if(there_is_collapse){
			player->points+=50;
		}
	}
	/*Ερωτημα vi*/
	int get_creation_floor(Object* creator){
		Cube *col_cube;

		if((col_cube = hasCollusion(creator,"y"))){
			double * col_cube_dir = creator->getDiretion();
			col_cube->setDirection(col_cube_dir);
			col_cube->update_target();
			return 1+get_creation_floor(col_cube);
		}

		return 1;
	}
	/*Ερωτημα vi*/
	void createCube(){
		Cube *cube,*col_cube,*standing_cube;
		int creation_floor,dir_x,dir_z;

		creation_floor = player->getYPos();
		dir_x = player->getDir_x();
		dir_z = player->getDir_z();

		player->setDirection(new double[3]{0,-1,0});
		player->update_target();
		if((standing_cube= hasCollusion(player,"y"))){
			if(standing_cube->apothema==0){
				player->setDirection(new double[3]{dir_x,0,dir_z});
				return;
			}
			else{
				standing_cube->apothema--;
				standing_cube->setColor(standing_cube->apothema);
				player->points+=5;
			}

		}

		player->setDirection(new double[3]{dir_x,0,dir_z});
		player->update_target();
		if((col_cube = hasCollusion(player,"z"))){
			double * col_cube_dir = new double[3]{0,1,0};
			col_cube->setDirection(col_cube_dir);
			col_cube->update_target();
			creation_floor += get_creation_floor(col_cube);
		}
		if(dir_x){
			cube=new Cube(sizeOfCube,player->getXPos()+dir_x*1,
					creation_floor,player->getZPos(),false);
		}

		else if(dir_z){
			cube=new Cube(sizeOfCube,player->getXPos(),
					creation_floor,player->getZPos()+dir_z*1,false);
		}

		if(cube!=NULL){
			cube->setRandomColor();
			cubes[creation_floor].push_back(cube);

		}
	}
	/*Ερώτημα viii*/
	void kick_cube(Object* kicker){
		Cube *col_cube;
		kicker->update_target();
		double *kicker_dir = kicker->getDiretion();
		col_cube = hasCollusion(kicker,"z");
		if(col_cube){
			col_cube->setDirection(kicker_dir);
			kick_cube(col_cube);
			col_cube->moveForward();
		}

	}
	/*Ερωτημα iv*/

	void delete_font_cube(){
		Cube *col_cube;
		player->update_target();

		if((col_cube = hasCollusion(player,"z"))){
			delete_Cube(col_cube);
		}
	}
	void delete_half_row(Object* bad_guy){
		Cube *col_cube;
		bad_guy->update_target();

		if((col_cube = hasCollusion(bad_guy,"z"))){
			col_cube->setDirection(bad_guy->getDiretion());
			delete_half_row(col_cube);

			delete_Cube(col_cube);
		}
	}

	void delete_half_collum(Object* bad_guy){
		Cube *col_cube;
		bad_guy->update_target();

		if((col_cube = hasCollusion(bad_guy,"y"))){
			col_cube->setDirection(bad_guy->getDiretion());
			delete_half_collum(col_cube);

			delete_Cube(col_cube);
		}
	}
	/*Ερωτημα v*/
	void delete_collum_row(){
		vector<Cube*>::iterator it;
		Cube *col_cube;
		double *direction = new double[3]{0,1,0};
		player->update_target();
		if((col_cube = hasCollusion(player,"z"))){
			//TODO MAybe not needed Delte the half row
			//col_cube->setDirection(player->getDiretion());
			//delete_half_row(col_cube);

			//Delete the whole Column
			col_cube->setDirection(direction);
			delete_half_collum(col_cube);
			direction[1] = -1; //update the y
			col_cube->setDirection(direction);
			delete_half_collum(col_cube);

			//Delete the front
			delete_Cube(col_cube);
			player->points-=5;
		}
	}
	/*Ερωτημα ix*/
	void handleCameraView(){
		if(v_Key_pressed_times%5 == 0){
			v_Key_pressed_times = 0;
			// Set the camera
			x_eye = player->getXPos();
			y_eye = player->getYPos()+3;
			z_eye = player->getZPos()-3;

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
	void showApothema(){
		Cube* cube;
		double *direction =player->getDiretion();

		player->setDirection(new double[3]{0,-1,0});
		player->update_target();

		if((cube = hasCollusion(player,"y"))){
		 glPushAttrib(GL_CURRENT_BIT);
		 glColor4f( 1.0, 1.0, 1.0,1.0);
		  glRasterPos3f(player->getXPos(), player->getYPos()+1,player->getZPos());
		  int len, i;
		  //string text="energy";
		  stringstream string_txt;
		  string_txt<<"Apothema: "<<cube->apothema<< endl;

		  len = string_txt.str().length();
		  //cout << len << endl;
		  for (i = 0; i < len; i++) {
		    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string_txt.str().c_str()[i]);
		  }
		 glPopAttrib();
		}
		player->setDirection(direction);
	}

	void energyText(){
		 glPushAttrib(GL_CURRENT_BIT);
		 glColor4f( 1.0, 1.0, 1.0,1.0);
		  glRasterPos3f(player->getXPos(), player->getYPos(),player->getZPos()-1);
		  int len, i;
		  //string text="energy";
		  stringstream string_txt;
		  string_txt<<"Total moves: "<<player->moves<<" Cur points: "<<player->points<< endl;

		  len = string_txt.str().length();
		  //cout << len << endl;
		  for (i = 0; i < len; i++) {
		    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string_txt.str().c_str()[i]);
		  }
		 glPopAttrib();
	}

	void processNormalKeys(int key, int xx, int yy) {
	        if (key == 27)
	              exit(0);
	}

	void pressKey(unsigned char key, int xx, int yy) {
		show_apothema=false;
	       switch (key) {
	             case 'w' : player->moveForward();checkIfHeClimbs();break;
	             case 's' : player->moveBackWard();break;
	             case 'a' : player->moveLeft(); break;
	             case 'd' : player->moveRight(); break;
	             case 'v' : v_Key_pressed_times++;break;
	             case 'e' : delete_collum_row();break;
	             case 'q' : delete_font_cube();break;
	             case 'r' : collapse();break;
	             case 'g' : show_apothema=true;break;
	             //TODO remove z, is for testing light Position
	             case 'z' : sun->setPosition(1.0f,3.0f,130.0f);break;
	             case 'x' : sun->setPosition(1.0f,1.0f,65.0f);break;
	             //Hide the sun
	             case 'c' : sun_to_view = !sun_to_view;sun->hide();cout<<"cubes: "<<cubes[0].size()<<endl;break;
	             case 'l' : tokens.push_back(new Token(player->getXPos(),
	            		 player->getYPos(),player->getZPos(),token_size_rad,player->moves));break;
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
		else if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			createCube();
		}
		else if(button==GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
			kick_cube(player);
		}
	}

	void createField(){
		bool center=false;
		for(int i=0;i<grid_size;i++){
					for(int j=0;j<grid_size;j++){
						Cube* tmp;
						if((i==grid_size/2&&j==grid_size/2)){
							center = true;
						}
						else{
							center = false;
						}
						tmp = new Cube(sizeOfCube,i,0,j,center);
						//tmp = new Cube(sizeOfCube,i*sizeOfCube+gap_size,0,j*sizeOfCube+gap_size,center);
						//tmp = new Cube(sizeOfCube,i*(sizeOfCube+gap_size),0,j*(sizeOfCube+gap_size),center);
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

		//SUN
		/*Ερώτημα iii*/
		int moves;
		moves = player->moves;
		sun->setPosition(moves%64+sun_start_x,moves%64+sun_start_y,sun_start_z);
		//TODO remove sun to view var
		if(moves<hide_sun_moves && sun_to_view){
			sun->view();
		}

		// Draw the TOkens
		for (vector<Token*>::iterator it = tokens.begin() ; it != tokens.end(); ++it){
			if((moves - (*it)->getCreatedTimeMove())<=hide_token_moves)
				(*it)->view();
			else{
				(*it)->~Token();
				tokens.erase(it);
				break;
			}
		}
		// Draw the GROUND
		//cout << "size 1: "<< cubes[0].size()<<endl;
		for(int floor=grid_floor;floor<grid_size;floor++){
			for (vector<Cube*>::iterator it = cubes[floor].begin() ; it != cubes[floor].end(); ++it){
				//Erase while cube is out of bounds
				if(( (*it)->isOutOfBounds() && !(*it)->isMoving())){
					cubes[floor].erase(it);
					break;
				}
				/*Cleans up cubes that are not belong in current  floor*/
				if((*it)->getDir_y()!=0&&(*it)->getYPos() < floor
						&& !(*it)->isMoving()){
					cout<< (*it)->getYPos() << " erase: "<< floor<<endl;
					cubes[floor].erase(it);
					break;
				}
				(*it)->view();
			}
		}

		//PLAyer view
		if(player->isOutOfBounds()){
			player->stopMoving();
			player->points-=20;
			player->setPosition(start_x,start_y,start_z);
		}else{
			player->view();
		}


		energyText();
		if(show_apothema)
			showApothema();
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
		glutSpecialFunc(processNormalKeys);
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

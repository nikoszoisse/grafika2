/*
 * World.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */
/*
#include "World.h"


World::World() {
	this->grid_size = 64;
}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::reshapeScene(int w,int h){

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

void World::renderScene(){
	//Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Reset transformations
	glLoadIdentity();

	float x=0.0f,z=5.0f;
	float lx=0.0f,lz=-1.0f;
	// Set the camera
	gluLookAt(	x, 1.0f, z,
			x+lx, 1.0f,  z+lz,
			0.0f, 1.0f,  0.0f);

        // Draw ground
	int count = 0;
	for(int i=0;i<cubes.size();i++){
		if(count%2){
			glColor3f(1.0f, 0.0f, 0.0f);
		}else{
			glColor3f(1.0f, 1.0f, 0.0f);
		}
		count++;
		cubes[i]->view();
	}

	glutSwapBuffers();
}
void World::init(int argc,char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Something Like Minecraft");

	for(int i=0;i<64;i++){
		for(int j=0;j<64;j++){
			cubes.push_back(new Cube(i,0,j+10,10));
		}
	}

	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshapeScene);
	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

}

void World::setGridSize(int gridSize){
	this->grid_size=gridSize;
}*/

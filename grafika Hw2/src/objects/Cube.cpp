/*
 * Cube.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#include "Cube.h"

Cube::Cube(float size,float distX,float distY,float distZ) {
	this->size = size;
	this->distX=distX;
	this->distY=distY;
	this->distZ=distZ;
	this->x=size/2+distX;
	this->y=size/2+distY;
	this->z=size/2+distZ;
	this->center = false;
	setColor();
}

Cube::~Cube() {
	// TODO Auto-generated destructor stub
}


void Cube::setColor(){
	if((x==size/2)&&(y==size/2)&&(z=size/2)&&distZ==0){
		color[0]=1.0;
		color[2]=1.0;
		center=true;
	}
	else{
		int number=rand()%4;
		if(number==0){
			color[0]=1.0;
		}
		else if(number==1){
			color[2]=1.0;
		}
		else if(number==2){
			color[1]=1.0;
		}
		else
		{
			color[0]=1.0;
			color[1]=1.0;
		}
	}
}

void Cube::createCube(float distanceX,float distanceY,float distanceZ){
	GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
	  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
	  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
	glBegin(GL_QUADS);
	// front face
	glColor3f(0.0,0.0,0.0);
	glNormal3fv(&n[0][0]);
	glVertex3f(size/2+distanceX,size/2+distanceY,size/2+distanceZ);
	glVertex3f(-size/2+distanceX,size/2+distanceY,size/2+distanceZ);
	glVertex3f(-size/2+distanceX,-size/2+distanceY,size/2+distanceZ);
	glVertex3f(size/2+distanceX,-size/2+distanceY,size/2+distanceZ);
	// left face
	glColor3f(0.0,0.0,0.0);
	glNormal3fv(&n[1][0]);
	glVertex3f(-size/2+distanceX,size/2+distanceY,size/2+distanceZ);
	glVertex3f(-size/2+distanceX,-size/2+distanceY,size/2+distanceZ);
	glVertex3f(-size/2+distanceX,-size/2+distanceY,-size/2+distanceZ);
	glVertex3f(-size/2+distanceX,size/2+distanceY,-size/2+distanceZ);
	// back face
	glColor3f(0.0,0.0,0.0);
	glNormal3fv(&n[2][0]);
	glVertex3f(size/2+distanceX,size/2+distanceY,-size/2+distanceZ);
	glVertex3f(-size/2+distanceX,size/2+distanceY,-size/2+distanceZ);
	glVertex3f(-size/2+distanceX,-size/2+distanceY,-size/2+distanceZ);
	glVertex3f(size/2+distanceX,-size/2+distanceY,-size/2+distanceZ);
	// right face
	glColor3f(0.0,0.0,0.0);
	glNormal3fv(&n[3][0]);
	glVertex3f(size/2+distanceX,size/2+distanceY,size/2+distanceZ);
	glVertex3f(size/2+distanceX,-size/2+distanceY,size/2+distanceZ);
	glVertex3f(size/2+distanceX,-size/2+distanceY,-size/2+distanceZ);
	glVertex3f(size/2+distanceX,size/2+distanceY,-size/2+distanceZ);
	// top face
	glColor3f(color[0],color[1],color[2]);
	glNormal3fv(&n[4][0]);
	glVertex3f(size/2+distanceX,size/2+distanceY,size/2+distanceZ);
	glVertex3f(-size/2+distanceX,size/2+distanceY,size/2+distanceZ);
	glVertex3f(-size/2+distanceX,size/2+distanceY,-size/2+distanceZ);
	glVertex3f(size/2+distanceX,size/2+distanceY,-size/2+distanceZ);
	// bottom face
	glColor3f(0.0,0.0,0.0);
	glNormal3fv(&n[5][0]);
	glVertex3f(size/2+distanceX,-size/2+distanceY,size/2+distanceZ);
	glVertex3f(-size/2+distanceX,-size/2+distanceY,size/2+distanceZ);
	glVertex3f(-size/2+distanceX,-size/2+distanceY,-size/2+distanceZ);
	glVertex3f(size/2+distanceX,-size/2+distanceY,-size/2+distanceZ);
glEnd();
}


void Cube::view(){
	createCube(distX,distY,distZ);
}

Cube* Cube::getCenter(){
	if(this->center==true){
		return this;
	}
	return NULL;
}

float Cube::getX(){
	return x;
}

float Cube::getY(){
	return y;
}

float Cube::getZ(){
	return z;
}

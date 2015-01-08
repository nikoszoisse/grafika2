/*
 * Cube.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#include "Cube.h"

Cube::Cube(float size,float distX,float distY,float distZ,bool center): Object(distX,distY,distZ) {
	this->size = size;
	this->distX=distX;
	this->distY=distY;
	this->distZ=distZ;
	this->x=size/2+distX;
	this->y=size/2+distY;
	this->z=size/2+distZ;
	this->field_center =center;
}

void Cube::setRandomColor(){
	if(field_center==true){
		color[0]=1.0;
		color[2]=1.0;
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
	//ALpa
	color[3] = 1.0;
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


Cube* Cube::getCenter(){
	if(this->field_center==true){
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

void Cube::view(){
	GLfloat *amb_color = new GLfloat[4]{0.1,0.1,0.1,1.0};//new GLfloat[4]{color[0]/2.0,color[1]/2.0,color[2]/2.0,1.0};
	applyMaterial(amb_color,color,new GLfloat[4]{1.0,1.0,1.0,1.0},50);
	createCube(distX,distY,distZ);
}

void Cube::setPosition(float x, float y, float z) {
}

Cube::~Cube() {
	// TODO Auto-generated destructor stub
}

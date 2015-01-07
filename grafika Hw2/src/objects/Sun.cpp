/*
 * Sun.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: zois
 */

#include "Sun.h"

/**
 * Creates an Object Sun
 */
Sun::Sun(float x,float y,float z,float radius)
		:Object(x,y,z),LightObject(x,y,z){
	this->radius = radius;
	this->color = new GLfloat[4]{255, 255, 34, 1};
}

Sun::~Sun() {
	// TODO Auto-generated destructor stub
}

void Sun::view(){
	this->enableLight();
	//Its right values for sun
	glPushMatrix();
	glTranslatef(x_point,y_point,z_point);
	glColor4f(255, 255, 34,0.3);
	GLfloat *amb = new GLfloat[4]{color[0]/2.0,color[1]/2.0,color[2]/2.0,1.0};
	//this->applyMaterial(amb,color,color,100);
    glutSolidSphere(radius,20,20);
    glPopMatrix();
}

void Sun::setPosition(float x,float y,float z){
	this->setObjPos(x,y,z);
	this->setLightPos(x,y,z-radius/2);
}

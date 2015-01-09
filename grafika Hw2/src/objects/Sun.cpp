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
	this->color = new GLfloat[4]{255, 255, 34, 1.0};
}

Sun::~Sun() {
	// TODO Auto-generated destructor stub
}

void Sun::view(){
	//Its right values for sun
	glPushMatrix();
	glTranslatef(x_point,y_point,z_point);
	glColor4f(color[0],color[1], color[2],color[3]);
	this->applyMaterial(color,color,color,20);
    glutSolidSphere(radius,20,20);
    glPopMatrix();
    //We wont anable it for other items not sun
	this->enableLight();
}

void Sun::setPosition(float x,float y,float z){
	this->setObjPos(x,y,z);
	this->setLightPos(x,y,z-radius/2);
}

float Sun::getWidth() {
	return this->radius*2;
}

void Sun::hide(){
	this->disableLight();
}

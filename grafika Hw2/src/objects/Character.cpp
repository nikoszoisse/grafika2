/*
 * Character.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#include "Character.h"

Character::Character(float x_pos,float y_pos,float z_pos):
		Object(x_pos,y_pos,z_pos) {
	// TODO Auto-generated constructor stub

}

void Character::view() {
	glPushMatrix();
		glRotatef(1.0,x_point,y_point,z_point);
		GLfloat *color = new GLfloat[4]{1.0,0.5,0.0,1.0};
		this->applyMaterial(color,color,color,50);
	    glutSolidSphere(0.5,20,20);
		//RENDERING legs klp
	glPopMatrix();
}

void Character::setPosition(float x, float y, float z) {
	this->setObjPos(x,y,z);
}

float Character::getXPos() {
	return x_point;
}

float Character::getYPos() {
	return y_point;
}

float Character::getZPos() {
	return z_point;
}

Character::~Character() {
}


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
		//glRotatef(rot_deg,x_pos,y_pos,z_pos);
		//glTranslateef();
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


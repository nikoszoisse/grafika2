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
		glRotatef(rot_deg,x_pos,y_pos,z_pos);
		//glTranslatef();
		//RENDERING legs klp
	glPopMatrix();
}

void Character::setPosition(float float1, float float2, float float3) {
}

float Character::getXPos() {
	return x_pos;
}

void Character::setXPos(float pos) {
	x_pos = pos;
}

float Character::getYPos() {
	return y_pos;
}

void Character::setYPos(float pos) {
	y_pos = pos;
}

float Character::getZPos() {
	return z_pos;
}

void Character::setZPos(float pos) {
	z_pos = pos;
}

Character::~Character() {
}


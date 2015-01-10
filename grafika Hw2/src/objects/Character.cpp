/*
 * Character.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#include "Character.h"
#include <iostream>
#include <math.h>
using namespace std;

Character::Character(float x_pos,float y_pos,float z_pos):
		Object(x_pos,y_pos,z_pos) {
	// TODO Auto-generated constructor stub
	this->on_move = false;
	this->on_rot = false;
	this->dir_x = 0;
	this->dir_y = 0;
	this->dir_z = 1;
	this->target_rot_deg=0;
	this->curr_rot_deg=0;
	this->clock_rot = 1;

}

void Character::view() {
	this->checkIfFinished();
	//Do Move animyion
	if(on_move && !on_rot){
		x_point += move_anim_frame*dir_x;
		y_point += move_anim_frame*dir_y;
	}
	//Do Rotate Animation
	if(on_rot){
		curr_rot_deg += rotate_anim_frame;
		if(abs(target_rot_deg) == curr_rot_deg){
			on_rot=false;
			moveForward();
		}
	}
	glPushMatrix();
		glTranslatef(x_point,y_point,z_point);
		glRotatef(clock_rot*curr_rot_deg,0,1,0);
		GLfloat *color = new GLfloat[4]{1.0,0.5,0.0,1.0};
		this->applyMaterial(color,color,color,new GLfloat[4]{1.0,0.5,0.0,0.5},50);
		renderCharBody();
		renderCharHead();
		renderCharHands();
		//RENDERING legs klp
	glPopMatrix();
}

void Character::renderCharHead(){
	glPushMatrix();
		glTranslatef(0,1,0);
		glutSolidSphere(0.2,10,10);
	glPopMatrix();
}

void Character::renderCharBody(){
	glPushMatrix();
		glTranslatef(0,0.2,0);
		glutSolidSphere(0.5,10,10);
	glPopMatrix();
}

void Character::renderCharHands(){
	glPushMatrix();
		glLineWidth(5);
		glBegin(GL_LINES);
			glColor4f(255,0,0,1.0);
			glVertex3f(-0.51,0.2,0);
			glVertex3f(-0.51,-0.2,0);
		glEnd();
		glBegin(GL_LINES);
			glColor4f(255,0,0,1.0);
			glVertex3f(0.51,0.2,0);
			glVertex3f(0.51,-0.2,0);
		glEnd();
	glPopMatrix();
}

void Character::renderCharLegs(){

}

void Character::moveForward(){
	z_target = z_point+char_step*dir_z;
	x_target = x_point+char_step*dir_x;
	y_target = y_point+char_step*dir_y;


	on_move=true;
}

void Character::moveBackWard(){
	if(on_rot)
		return;

	if(dir_z){
		dir_z *=(-1);
		dir_x = 0;
	}
	else if(dir_x){
		dir_x *=(-1);
		dir_z = 0;
	}

	on_rot = true;
	//this->curr_rot_deg = 0*dir_z + curr_rot_deg*dir_x*dir_x;
	//target_rot_deg= 180*dir_z + 180*dir_x + dir_x*curr_rot_deg + dir_z*curr_rot_deg;
	this->target_rot_deg = 180+curr_rot_deg;
	this->clock_rot = dir_x + dir_z;

	moveForward();
}

void Character::moveLeft(){
	if(on_rot)
		return;
	if(dir_z){
		dir_x= dir_z;
		dir_z = 0;
	}
	else if(dir_x){
		dir_z=-1*dir_x;
		dir_x = 0;
	}

	on_rot = true;
	clock_rot = 1;
	target_rot_deg=90+curr_rot_deg;
	//this->clock_rot = dir_x + dir_z;
	moveForward();
}

void Character::moveRight(){
	if(on_rot)
		return;
	if(dir_z){
		dir_x = -1*dir_z;
		dir_z = 0;
	}
	else if(dir_x){
		dir_z = dir_x;
		dir_x=0;
	}

	on_rot = true;
	clock_rot = -1;
	target_rot_deg=90+curr_rot_deg;
	moveForward();
}

void Character::checkIfFinished(){
	if(fabs(dir_x*x_point-dir_x*x_target)<=0.1 && fabs(dir_y*y_point-dir_y*y_target)<=0.1 &&
			(fabs(dir_z*z_point-dir_z*z_target)<=0.1) && !on_rot){
		on_move=false;
		target_rot_deg=0;
	}
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


bool Character::isMoving(){
	return on_move;
}

float Character::getWidth(){
	return 1;
}

Character::~Character() {
}

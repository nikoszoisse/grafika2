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
	this->width = 0.5;
	this->moves = 0;
}

void Character::view() {
	this->checkIfFinished();
	//Do Move animyion
	if((on_move && !on_rot) || (on_jump && on_rot)){
		x_point += move_anim_frame*dir_x;
		z_point +=move_anim_frame*dir_z;
		y_point += move_anim_frame*dir_y;
	}
	//Do Rotate Animation
	if(on_rot || on_jump){
		on_move=false;
		curr_rot_deg += rotate_anim_frame;
		if(abs(target_rot_deg) <= curr_rot_deg){
			on_rot=false;
			//on_move=true;
			//moveForward();
		}
	}
	glPushMatrix();
		glTranslatef(x_point,y_point,z_point);
		glRotatef(clock_rot*curr_rot_deg,0,1,0);
		renderCharBody();
		renderCharHead();
		renderCharHands();
		renderCharLegs();
		//RENDERING legs klp
	glPopMatrix();
}

void Character::renderCharHead(){
	glPushMatrix();
		GLfloat *color = new GLfloat[4]{1.0,0.0,0.0,1.0};
		this->applyMaterial(color,color,color,50);
		glTranslatef(0,0.8,0);
		glutSolidSphere(0.15,10,10);
	glPopMatrix();
}

void Character::renderCharBody(){
	glPushMatrix();
		GLfloat *color = new GLfloat[4]{0.0,0.0,1.0,1.0};
		this->applyMaterial(color,color,color,50);
		glTranslatef(0,0.5,0);
		glutSolidCube(0.3);
	glPopMatrix();
}

void Character::renderCharHands(){
	glPushMatrix();
		glLineWidth(10);
		if(on_move){
			glRotatef(90,0.01,0.0,0.0);
			glTranslatef(0.0,-0.1,-0.5);
		}
		glBegin(GL_LINES);
			glColor4f(255,0,0,1.0);
			glVertex3f(-0.177,0.4,0);
			glVertex3f(-0.177,0.2,0);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		if(on_move){
			glRotatef(270,0.01,0,0);
			glTranslatef(0.0,-0.1,0.5);
		}
		glLineWidth(10);
		glBegin(GL_LINES);
			glColor4f(255,0,0,1.0);
			glVertex3f(0.177,0.4,0);
			glVertex3f(0.177,0.2,0);
		glEnd();
	glPopMatrix();
}

void Character::renderCharLegs(){
	glPushMatrix();
		glLineWidth(10);
		if(on_move){
			glRotatef(225,-0.01,0.0,0.0);
			glTranslatef(0.0,-0.3,-0.35);
		}
		glBegin(GL_LINES);
			glColor4f(255,0,0,1.0);
			glVertex3f(-0.05,0.0,0);
			glVertex3f(-0.05,0.3,0);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		if(on_move){
			glRotatef(105,-0.01,0.0,0.0);
			glTranslatef(0.0,0.0,0.35);
		}
		glBegin(GL_LINES);
			glColor4f(255,0,0,1.0);
			glVertex3f(0.05,0.0,0);
			glVertex3f(0.05,0.3,0);
		glEnd();
	glPopMatrix();
}
void Character::update_target(){
	z_target = z_point+(char_step+gap_size*sizeOfCube)*dir_z;
	x_target = x_point+(char_step+gap_size*sizeOfCube)*dir_x;
	y_target = y_point+char_step*dir_y;
}

void Character::moveForward(){
	if(on_move)
		return;
	x_target = x_point;
	y_target = y_point;
	z_target = z_point;
	update_target();

	on_move=true;
	this->moves++;
}

void Character::moveBackWard(){
	if(on_rot || on_move)
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

	//moveForward();
}

void Character::moveLeft(){
	if(on_rot || on_move)
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
	//moveForward();
}

void Character::moveRight(){
	if(on_rot || on_move)
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
	//moveForward();
}

void Character::setPosition(float x, float y, float z) {
	this->setObjPos(x,y,z);
}


void Character::moveUp() {
	dir_y = 1;
	on_rot = true;
	on_jump = true;
	clock_rot = -1;
	target_rot_deg = 360;
}

void Character::moveDown() {
}

Character::~Character() {
}

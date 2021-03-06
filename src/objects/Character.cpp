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

Character::Character(double x_pos,double y_pos,double z_pos):
		Object(x_pos,y_pos,z_pos) {
	// TODO Auto-generated constructor stub
	this->width = 0.5;
	this->moves = 0;
	this->points=start_points;
	this->dir_z=1;
	this->dir_x=0;
	this->dir_y=0;
	this->tokens = start_num_tokens;
}

void Character::view() {
	this->checkIfFinished();
	//Do Move animyion
	if((on_move && !on_rot)){
		x_point += move_anim_frame*dir_x;
		y_point += move_anim_frame*dir_y;
		z_point += move_anim_frame*dir_z;
	}
	//Do Rotate Animation
	if(on_rot){
		//on_move=false;
		curr_rot_deg += rotate_anim_frame;
		if(fabs(target_rot_deg) <= curr_rot_deg){
			on_rot=false;
		}
	}
	glPushMatrix();
		glTranslatef(x_point,y_point,z_point/*+dir_x/2.0*/);
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
	z_target = z_point+char_step*dir_z;
	x_target = x_point+char_step*dir_x;
	y_target = y_point+char_step*dir_y;
	this->x_target = round(x_target);
	this->y_target = round(y_target);
	this->z_target = round(z_target);

}

void Character::moveForward(){
	if(on_move)
		return;
	x_target = x_point;
	y_target = y_point;
	z_target = z_point;
	update_target();

	on_move=true;
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

void Character::setPosition(double x, double y, double z) {
	this->setObjPos(x,y,z);
}


void Character::moveUp() {
	dir_y = 1;
	on_rot = true;
	jumping = true;
	clock_rot = -1;
	target_rot_deg = 360;
	this->update_target();
}

void Character::checkIfFinished(){
	if(fabs(dir_x*x_point-dir_x*x_target)<=0.1 && fabs(dir_y*y_point-dir_y*y_target)<=0.1 &&
			(fabs(dir_z*z_point-dir_z*z_target)<=0.1) && !on_rot){

		this->moves++;

		this->x_point = round(x_point);
		this->y_point = round(y_point);
		this->z_point = round(z_point);
		this->stopMoving();
	}
}

/*bool Character::isOutOfBounds(){
	if(this->x_point>grid_size||this->y_point<grid_floor||
				this->z_point>grid_size){
			return true;
	}

	return false;
}*/

void Character::moveDown() {
	if(on_move)
		return;
	dir_x=0;
	dir_y=-1;
	dir_z=0;
	falling = true;
	moveForward();
}
 void Character::restore(){
		this->dir_x = 0;
		this->dir_y = 0;
		this->dir_z = 1;
		this->on_move = false;
		this->on_rot = false;
		this->jumping = false;
		this->falling = false;
		this->target_rot_deg=0;
		this->curr_rot_deg=0;
		this->clock_rot = 1;
 }
Character::~Character() {
}

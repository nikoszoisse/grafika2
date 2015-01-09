/*
 * Character.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#include "Character.h"
#include <iostream>
using namespace std;

Character::Character(float x_pos,float y_pos,float z_pos):
		Object(x_pos,y_pos,z_pos) {
	// TODO Auto-generated constructor stub
	this->on_move = false;
	this->on_rot = false;
	this->dir_x = 0;
	this->dir_y = 0;
	this->dir_z = 1;
	this->rot_deg=0;

}

void Character::view() {
	int rot;
	rot = 0;
	this->checkIfFinished();

	if(on_move && !on_rot){
		x_point += 0.01*x_target*dir_x;
		y_point += 0.01*y_target*dir_y;
		z_point += 0.01*z_target*dir_z;
	}
	//cout << z_point << " "<< y_point <<" "<< x_point<<endl;
	if(on_rot && rot_deg){
		rot = this->rot_deg - this->rot_deg-1;
		this->rot_deg--;
		if(rot_deg==0){
			on_rot=false;
			moveForward();
		}
	}
	glPushMatrix();
		glRotatef(rot,0,1,0);
		glTranslatef(x_point,y_point,z_point);
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
		//glTranslatef(x_point,y_point,z_point);
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
	z_target = z_point+1.0*dir_z;
	x_target = x_point+1.0*dir_x;
	y_target = y_point+1.0*dir_y;
	on_move=true;
	if(this->rot_deg == 0){
		on_rot=false;
	}
}

void Character::moveBackWard(){
	z_target=this->getZPos()-1;
	if(dir_z){
		dir_z *=(-1);
		dir_x = 0;
	}
	else if(dir_x){
		dir_x *=(-1);
		dir_z = 0;
	}

	on_rot = true;
	rot_deg=180;
	moveForward();
}

void Character::moveLeft(){
	x_target=this->getXPos()-1;
	if(dir_z){
		dir_x=-1*dir_z;
		dir_z = 0;
	}
	else if(dir_x){
		dir_z=dir_x;
		dir_x = 0;
	}

	on_rot = true;
	rot_deg=270;
	moveForward();
}

void Character::moveRight(){
	x_target=this->getXPos()+1;

	if(dir_z){
		dir_x = dir_z;
		dir_z = 0;
	}
	else if(dir_x){
		dir_z = -1*dir_x;
		dir_x=0;
	}

	on_rot = true;
	rot_deg=90;
	moveForward();
}
void Character::checkIfFinished(){
	if(x_point>=x_target&&y_point>=y_target&&
			z_point>=z_target){
		on_move=false;

		rot_deg=0;
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

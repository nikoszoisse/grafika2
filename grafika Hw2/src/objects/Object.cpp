/*
 * Object.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#include "Object.h"
#include <iostream>
#include <math.h>
using namespace std;
Object::Object(float x,float y,float z) {
	this->x_point = x;
	this->y_point = y;
	this->z_point = z;
	this->x_target = x;
	this->y_target = y;
	this->z_target = z;
	this->dir_x = 0;
	this->dir_y = 0;
	this->dir_z = 1;
	this->width = 0;
	this->on_move = false;
	this->on_rot = false;
	this->on_jump = false;
	this->target_rot_deg=0;
	this->curr_rot_deg=0;
	this->clock_rot = 1;

	this->ID = ++created_objects;

	ambient_color = new GLfloat[4]{0.2, 0.2, 0.2, 1.0};
	//to xrwma p diaxeetai
	diffuse_color = new GLfloat[4]{0.8, 0.8, 0.8, 1.0};
	//GUalada se korufes p.x
	specular_color = new GLfloat[4]{0.0, 0.0, 0.0, 1.0};
	//To Xrwma pou ekpempei
	emission_color = new GLfloat[4]{0.0, 0.0, 0.0, 0.5};

	//shinness of specular
	shininess = 0.0;
}
/**
 * Set the Object Position
 * @param x_pos
 * @param y_pos
 * @param z_pos
 */
void Object::setObjPos(float x_pos, float y_pos, float z_pos) {
	this->x_point = x_pos;
	this->y_point = y_pos;
	this->z_point = z_pos;
}
/**
 * Apply MAterial to an Object with default values
 */
void Object::applyMaterial() {
	  	  	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, this->ambient_color);
	        glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,  this->diffuse_color);
	        glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, this->specular_color);
	        glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, this->emission_color);
	        glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, this->shininess);
}
/**
 * Apply MAterial to an Object
 *
 * @param ambient_color
 * @param diffuse_color
 * @param specular_color
 * @param shininess
 */
void Object::applyMaterial(GLfloat *ambient_color,GLfloat *diffuse_color
		,GLfloat *specular_color,GLfloat shininess) {
	this->ambient_color = ambient_color;
	this->diffuse_color = diffuse_color;
	this->specular_color = specular_color;
	this->shininess = shininess;
	this->applyMaterial();
}

/**
 * Apply MAterial to an Object
 *
 * @param ambient_color
 * @param diffuse_color
 * @param specular_color
 * @param emission_color
 * @param shininess
 */
void Object::applyMaterial(GLfloat *ambient_color,GLfloat *diffuse_color
		,GLfloat *specular_color, GLfloat *emission_color,GLfloat shininess) {
	this->emission_color = emission_color;

	this->applyMaterial(ambient_color,diffuse_color,specular_color,shininess);
}
/**
 * Returns an array (size 3) with coordinates of object
 * @return float*
 */
float* Object::getObjPosition() {
	return new float[3]{x_point,y_point,z_point};
}

float* Object::getTargetPosition() {
	return new float[3]{x_target,y_target,z_target};
}

/**
 * @param Object* target
 * @return true if here is collision between this object(target coordinates) and the targeted object
 *
 */

bool Object::hasCollision(Object* target) {
	float *pos=target->getObjPosition();
	/*cout <<"x " << x_target <<" "<< pos[0]<<endl;
	cout <<"y " << y_target <<" "<< pos[1]<<endl;
	cout <<"z " << z_target <<" "<< pos[2]<<endl;*/
	if((pos[0]<=this->x_target+gap_size&&pos[0]+1>=x_target+gap_size)&&
			(pos[1]<=this->y_target&&pos[1]+1>=y_target)&&
			(pos[2]<=this->z_target+gap_size&&pos[2]+1>=z_target+gap_size)){
		return true;
	}

	return false;
}

void Object::checkIfFinished(){
	if(fabs(dir_x*x_point-dir_x*x_target)<=0.1 && fabs(dir_y*y_point-dir_y*y_target)<=0.1 &&
			(fabs(dir_z*z_point-dir_z*z_target)<=0.1) && !on_rot){
		on_move=false;
		on_jump=false;
		target_rot_deg=0;
	}
}

float Object::getWidth(){
	return width;
}

float* Object::getDiretion() {
	return new float[3]{dir_x,dir_y,dir_z};
}

float Object::getXPos() {
	return x_point;
}

float Object::getYPos() {
	return y_point;
}

void Object::stopMoving() {
	on_move=false;
	on_jump=false;
	target_rot_deg=0;
}

float Object::getZPos() {
	return z_point;
}


bool Object::isMoving(){
	return on_move;
}

int Object::getDir_z(){
	return dir_z;
}

int Object::getDir_y(){
	return dir_y;
}

int Object::getDir_x(){
	return dir_x;
}

void Object::setDirection(float* direction) {
	this->dir_x = direction[0];
	this->dir_y = direction[1];
	this->dir_z = direction[2];
}

bool Object::isOutOfBounds(){
	/*Out of Bundaries*/
	if(this->x_point>grid_size||this->y_point>grid_size||
			this->z_point>grid_size){
		return true;
	}

	if(this->x_target>grid_size||this->y_target>grid_size||
			this->z_target>grid_size){
		return true;
	}

	if(this->x_point<grid_floor||this->y_point<grid_floor||
			this->z_point<grid_floor){
		return true;
	}

	if(this->x_target<grid_floor||this->y_target<grid_floor||
			this->z_target<grid_floor){
		return true;
	}

	return false;
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}


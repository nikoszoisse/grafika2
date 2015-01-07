/*
 * Object.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#include "Object.h"

Object::Object(float x,float y,float z) {
	this->x_point = x;
	this->y_point = y;
	this->z_point = z;
	ambient_color = new GLfloat[4]{0.2, 0.2, 0.2, 1.0};
	//to xrwma p diaxeetai
	diffuse_color = new GLfloat[4]{0.8, 0.8, 0.8, 1.0};
	//GUalada se korufes p.x
	specular_color = new GLfloat[4]{0.0, 0.0, 0.0, 1.0};
	//To Xrwma pou ekpempei
	emission_color = new GLfloat[4]{0.0, 0.0, 0.0, 1.0};

	shininess = 0.0;
}

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

Object::~Object() {
	// TODO Auto-generated destructor stub
}


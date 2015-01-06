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
/**
 * Apply MAterial to an Object
 */
void Object::applyMaterial() {
	  	  	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, this->ambient_color);
	        glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,  this->diffuse_color);
	        glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, this->specular_color);
	        glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, this->emission_color);
	        glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, this->shininess);
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}


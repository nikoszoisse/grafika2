/*
 * Token.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: zois
 */

#include "Token.h"

/**
 * Creates an Object Token
 */
Token::Token(float x,float y,float z,float radius)
		:Object(x,y,z),LightObject(x,y,z+5){
	this->radius = radius;
	this->color = new GLfloat[4]{1.0, 0, 0, 1};
	this->quadraticAttenuation = 0.2f;
	this->spotExponent = 0.0f;
	this->spotCutoff = 180.0f;
	this->setSpotDirection(1,0,0);
}

Token::~Token() {
	// TODO Auto-generated destructor stub
}

void Token::view(){
	//Its right values for Token
	glPushMatrix();
	glTranslatef(x_point,y_point,z_point);
	GLfloat *amb = new GLfloat[4]{color[0]/2.0,color[1]/2.0,color[2]/2.0,1.0};
	GLfloat *spe = new GLfloat[4]{1.0,0.4,0.0,1.0};
	this->applyMaterial(amb,color,spe,color,20);
	glColor4f(color[0],color[1], color[2],color[3]);
    glutSolidSphere(radius,20,20);
    glPopMatrix();

	this->enableLight();
}

void Token::setPosition(float x,float y,float z){
	this->setObjPos(x,y,z);
	this->setLightPos(x,y,z-radius/2);
}

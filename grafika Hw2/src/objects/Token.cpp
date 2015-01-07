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
		:Object(x,y,z),LightObject(x,y,z){
	this->radius = radius;
	this->color = new GLfloat[4]{255, 0, 0, 1};
	this->qaDiffuseLight = color;
	this->qaAmbientLight = color;
	this->constantAttenuation = 0.0f;
	this->quadraticAttenuation = 1.0f;
	this->setSpotDirection(x,y,z);
}

Token::~Token() {
	// TODO Auto-generated destructor stub
}

void Token::view(){
	this->enableLight();
	//Its right values for Token
	glPushMatrix();
	glTranslatef(x_point,y_point,z_point);
	GLfloat *amb = new GLfloat[4]{color[0]/2.0,color[1]/2.0,color[2]/2.0,1.0};
	GLfloat *spe = new GLfloat[4]{255,255,255,1.0};

	this->applyMaterial(amb,color,spe,color,50);
    glutSolidSphere(radius,20,20);
    glPopMatrix();
}

void Token::setPosition(float x,float y,float z){
	this->setObjPos(x,y,z);
	this->setLightPos(x,y,z-radius/2);
}

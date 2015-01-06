/*
 * LightObject.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#include "LightObject.h"

/**
 * Set Up the Positon of Light
 * @param x_pos
 * @param y_pos
 * @param z_pos
 */
LightObject::LightObject(float x_pos,float y_pos,float z_pos) {
	lightId = GL_LIGHT0;

	// Set lighting intensity and color
	qaAmbientLight = new GLfloat[4]{0.2, 0.2, 0.2, 1.0};
	qaDiffuseLight = new GLfloat[4]{0.8, 0.8, 0.8, 1.0};
	qaSpecularLight = new GLfloat[4]{1.0, 1.0, 1.0, 1.0};
	// Light source position
	qaLightPosition    = new GLfloat[4]{0.5, 0, -3.5, 0.5};

	spotExponent = 0.0;
	spotCutoff = 180.0f;

	spotDirection = new GLfloat[4]{0.0,0.0,1.0};

	constantAttenuation = 1.0;
	linearAttenuation = 0.0;
	quadraticAttenuation = 0.0;
}

LightObject::LightObject(){
	lightId = GL_LIGHT0;

	// Set lighting intensity and color
	qaAmbientLight = new GLfloat[4]{0.2, 0.2, 0.2, 1.0};
	qaDiffuseLight = new GLfloat[4]{0.8, 0.8, 0.8, 1.0};
	qaSpecularLight = new GLfloat[4]{1.0, 1.0, 1.0, 1.0};
	// Light source position
	qaLightPosition    = new GLfloat[4]{0.5, 0, -3.5, 0.5};

	spotExponent = 0.0;
	spotCutoff = 180.0f;

	spotDirection = new GLfloat[4]{0.0,0.0,1.0};

	constantAttenuation = 1.0;
	linearAttenuation = 0.0;
	quadraticAttenuation = 0.0;
}

/**
 * Enables The light of an Object
 */
void LightObject::enableLight() {
    // Enable lighting
	glDisable(GL_LIGHTING);
     glEnable(this->lightId);
		glLightfv( lightId, GL_AMBIENT, this->qaAmbientLight);
		glLightfv( lightId, GL_DIFFUSE, this->qaDiffuseLight);
		glLightfv( lightId, GL_SPECULAR, this->qaSpecularLight);
		glLightfv( lightId, GL_POSITION, this->qaLightPosition);
		glLightfv( lightId, GL_SPOT_DIRECTION, this->spotDirection);
		glLightf( lightId, GL_SPOT_EXPONENT, this->spotExponent);
		glLightf( lightId, GL_SPOT_CUTOFF, this->spotCutoff);
		glLightf( lightId, GL_CONSTANT_ATTENUATION, this->constantAttenuation);
		glLightf( lightId, GL_LINEAR_ATTENUATION, this->linearAttenuation);
		glLightf( lightId, GL_QUADRATIC_ATTENUATION, this->quadraticAttenuation);
	glEnable(GL_LIGHTING);
}

/**
 * Disable the Light of an object
 */
void LightObject::disableLight() {
    glDisable(this->lightId);
}

LightObject::~LightObject() {
	// TODO Auto-generated destructor stub
}


/*
 * LightObject.h
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#ifndef SRC_LIGHTOBJECT_H_
#define SRC_LIGHTOBJECT_H_

#include "Object.h"
static int num_of_lights = 0;

#include<iostream>
using namespace std;

class LightObject{
private:
	GLenum 	lightId;

	// Light source position
	GLfloat *qaLightPosition;

protected:

	// Set lighting intensity and color
	GLfloat *qaAmbientLight;
	GLfloat *qaDiffuseLight;
	GLfloat *qaSpecularLight;
	GLfloat  spotExponent;
	GLfloat  spotCutoff;
	//Eksasthenshsh fwtos 1/ athroisma attentuations
	GLfloat  constantAttenuation;
	GLfloat  linearAttenuation;
	GLfloat  quadraticAttenuation;

	GLfloat *spotDirection;		//Normalized Vector

	LightObject(double,double,double);
	void enableLight();
	void disableLight();
	void setLightPos(double,double,double);
	void setSpotDirection(double,double,double);
public:
	LightObject();
	virtual ~LightObject();
};


#endif /* SRC_LIGHTOBJECT_H_ */

/*
 * LightObject.h
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#ifndef SRC_LIGHTOBJECT_H_
#define SRC_LIGHTOBJECT_H_

#include "Object.h"

class LightObject{
private:
	static int num_of_lights=0;
	GLenum 	lightId;

	// Light source position
	GLfloat *qaLightPosition;

	GLfloat *spotDirection;
protected:
	// Set lighting intensity and color
	GLfloat *qaAmbientLight;
	GLfloat *qaDiffuseLight;
	GLfloat *qaSpecularLight;
	GLfloat  spotExponent;
	GLfloat  spotCutoff;
	GLfloat  constantAttenuation;
	GLfloat  linearAttenuation;
	GLfloat  quadraticAttenuation;

	LightObject(float,float,float);
	void enableLight();
	void disableLight();
	void setLightPos(float,float,float);
	void setSpotDirection(float,float,float);
public:
	LightObject();
	virtual ~LightObject();
};

#endif /* SRC_LIGHTOBJECT_H_ */

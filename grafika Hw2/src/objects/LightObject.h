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
	GLenum 	lightId;

	// Set lighting intensity and color
	GLfloat *qaAmbientLight;
	GLfloat *qaDiffuseLight;
	GLfloat *qaSpecularLight;
	GLfloat *emitLight;
	GLfloat *Noemit;
	// Light source position
	GLfloat *qaLightPosition;

	GLfloat  spotExponent;
	GLfloat  spotCutoff;

	GLfloat *spotDirection;

	GLfloat  constantAttenuation;
	GLfloat  linearAttenuation;
	GLfloat  quadraticAttenuation;

protected:
	LightObject(float,float,float);
	void disableLight();
public:
	LightObject();
	//TODO go to protected
	void enableLight();
	virtual ~LightObject();
};

#endif /* SRC_LIGHTOBJECT_H_ */

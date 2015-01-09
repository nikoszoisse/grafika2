/*
 * Sun.h
 *
 *  Created on: Jan 7, 2015
 *      Author: zois
 */
#include "Object.h"
#include "LightObject.h"

#ifndef SUN_H_
#define SUN_H_

class Sun : public Object,LightObject{
private:
	GLfloat radius;
	GLfloat *color;
public:
	Sun(float,float,float,float);
	virtual ~Sun();
	void view();
	void setPosition(float,float,float);
	float getWidth();
	void hide();
};

#endif /* SUN_H_ */

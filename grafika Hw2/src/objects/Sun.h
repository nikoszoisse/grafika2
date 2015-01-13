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
	Sun(double,double,double,double);
	void hide();

	void view();
	void setPosition(double,double,double);

	void moveForward(); /*Moves to x, or z*/
	void moveBackWard(); /*ROtates/ ,Update dir z and call moveFoward*/
	void moveLeft();	/*Rotate update dir x and call movefoward*/
	void moveRight();	/**/
	void moveUp();
	void moveDown();
	void update_target();


	virtual ~Sun();
};

#endif /* SUN_H_ */

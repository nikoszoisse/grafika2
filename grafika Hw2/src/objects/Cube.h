/*
 * Cube.h
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "Object.h"
#include "settings.h"

class Cube: public Object {
	private:
	//float x,y,z;
	GLfloat *color;
	bool field_center;
	void createCube(float,float,float);
public:
	int apothema;
	Cube(float,float,float,float,bool);
	Cube* getCenter();
	void view();
	void setPosition(float,float,float);
	/*float getX();
	float getY();
	float getZ();*/

	void setRandomColor();
	void setColor(GLfloat*);
	void moveForward(); /*Moves to x, or z*/
	void moveBackWard(); /*ROtates/ ,Update dir z and call moveFoward*/
	void moveLeft();	/*Rotate update dir x and call movefoward*/
	void moveRight();	/**/
	void moveUp();
	void moveDown();
	void update_target();
	int getApothema();
	void setApothema(int);

	virtual ~Cube();
};

#endif /* CUBE_H_ */

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
	float size,distX,distY,distZ;
	float x,y,z;
	GLfloat *color;
	bool field_center;
	void createCube(float,float,float);
public:
	Cube(float,float,float,float,bool);
	Cube* getCenter();
	void view();
	void setPosition(float,float,float);
	float getX();
	float getY();
	float getZ();
	float getWidth();
	void setRandomColor();
	void setColor(GLfloat*);
	virtual ~Cube();
};

#endif /* CUBE_H_ */

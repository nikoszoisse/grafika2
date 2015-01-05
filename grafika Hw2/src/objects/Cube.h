/*
 * Cube.h
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "Object.h"


class Cube: public Object {
	private:
	float size,distX,distY,distZ;
	float x,y,z;
	float color[3];
	bool center=false;
	void createCube(float,float,float);
	void setColor();
public:
	Cube(float,float,float,float);
	Cube* getCenter();
	void view();
	float getX();
	float getY();
	float getZ();
	virtual ~Cube();
};

#endif /* CUBE_H_ */

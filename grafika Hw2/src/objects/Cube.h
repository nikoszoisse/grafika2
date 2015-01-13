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
#include <math.h>
class Cube: public Object {
	private:
	//double x,y,z;
	GLfloat *color;
	bool hidden;
	bool field_center;
	void createCube(double,double,double);
public:
	int apothema;
	bool isHidden() const;
	void hide();
	Cube(double,double,double,double,bool);
	Cube* getCenter();
	void view();
	void setPosition(double,double,double);
	/*double getX();
	double getY();
	double getZ();*/

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

/*
 * Token.h
 *
 *  Created on: Jan 7, 2015
 *      Author: zois
 */
#include "Object.h"
#include "LightObject.h"

#ifndef Token_H_
#define Token_H_

class Token : public Object,LightObject{
private:
	GLfloat radius;
	GLfloat *color;
	int created_time_move;
public:
	Token(double,double,double,double,int);
	virtual ~Token();
	void view();
	void setPosition(double,double,double);
	void moveForward(); /*Moves to x, or z*/
	void moveBackWard(); /*ROtates/ ,Update dir z and call moveFoward*/
	void moveLeft();	/*Rotate update dir x and call movefoward*/
	void moveRight();	/**/
	void moveUp();
	void moveDown();
	void update_target();

	int getCreatedTimeMove() const;

};

#endif /* Token_H_ */

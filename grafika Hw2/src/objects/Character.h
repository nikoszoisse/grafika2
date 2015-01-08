/*
 * Character.h
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Object.h"


class Character: public Object{
private:
	float x_pos;
	float y_pos;
	float z_pos;
	float x_target,y_target,z_target;
	bool on_move;
	int dir_z; /*1,-1*/
	int dir_x;
	int dir_y;
	float rot_deg; /*movefowarrd:0,movrelft,right 90,270, move_back: 180*/
public:
	Character(float,float,float);
	void view();
	void setPosition(float,float,float);
	void renderCharLegs();
	void renderCharBody();
	void renderCharHands();
	void renderCharHead();
	/*Temp point(to go) from char x,y,z coordinates*/
	void moveForward(); /*Moves to x, or z*/
	void moveBackWard(); /*ROtates/ ,Update dir z and call moveFoward*/
	void moveLeft();	/*Rotate update dir x and call movefoward*/
	void moveRight();	/**/
	virtual ~Character();
	float getXPos();
	void setXPos(float);
	float getYPos();
	void setYPos(float);
	float getZPos();
	void setZPos(float);
};

#endif /* CHARACTER_H_ */

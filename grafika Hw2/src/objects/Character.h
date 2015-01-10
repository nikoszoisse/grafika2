/*
 * Character.h
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Object.h"
#include "settings.h"

class Character: public Object{
private:
	//TODO Move to Animation
	bool on_move;
	bool on_rot;

	float target_rot_deg; /*movefowarrd:0,movrelft,right 90,270, move_back: 180*/
	float curr_rot_deg; /*Where  to start rotatiing Default =0*/
	float clock_rot;
	float motion;
	void checkIfFinished();
public:
	Character(float,float,float);
	bool isMoving();
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
	void stopMoving();
	float getWidth();
	virtual ~Character();
	float getXPos();
	void setXPos(float);
	float getYPos();
	void setYPos(float);
	float getZPos();
	void setZPos(float);
};

#endif /* CHARACTER_H_ */

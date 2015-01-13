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
	void renderCharLegs();
	void renderCharBody();
	void renderCharHands();
	void renderCharHead();
public:
	int moves;
	int points;
	Character(double,double,double);
	void view();
	void setPosition(double,double,double);
	/*Temp point(to go) from char x,y,z coordinates*/
	void moveForward(); /*Moves to x, or z*/
	void moveBackWard(); /*ROtates/ ,Update dir z and call moveFoward*/
	void moveLeft();	/*Rotate update dir x and call movefoward*/
	void moveRight();	/**/
	void moveUp();
	void moveDown();
	void update_target();

	void checkIfFinished();
	virtual ~Character();
};

#endif /* CHARACTER_H_ */

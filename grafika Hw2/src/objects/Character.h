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
public:
	Character(float,float,float);
	void view();
	void setPosition(float,float,float);
	virtual ~Character();
};

#endif /* CHARACTER_H_ */

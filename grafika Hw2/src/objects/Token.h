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
public:
	Token(float,float,float,float);
	virtual ~Token();
	void view();
	void set_range_cons();
	void set_range_qua();
	void set_range_lin();
	void setPosition(float,float,float);
	void reset_range();
};

#endif /* Token_H_ */

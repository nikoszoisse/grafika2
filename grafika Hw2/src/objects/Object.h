/*
 * Object.h
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#ifndef SRC_OBJECT_H_
#define SRC_OBJECT_H_

#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "settings.h"

static int created_objects = 0;

class Object {
protected:
	/*
	 *  For the glMaterial, it's usual to set the Ambient and Diffuse colours to
	 *    the natural colour of the object and to put the Specular colour to white.
	 *   The emission colour is generally black for objects that do not shine by their own light.
	 */
	double x_point,y_point,z_point;
	double x_target,y_target,z_target;
	double dir_z; /*1,-1*/
	double dir_x;
	double dir_y;
	double width;
	//Animations
	bool on_move;
	bool on_rot;
	bool jumping;
	bool falling;
	double target_rot_deg; /*movefowarrd:0,movrelft,right 90,270, move_back: 180*/
	double curr_rot_deg; /*Where  to start rotatiing Default =0*/
	double clock_rot;
	double motion;

	void applyMaterial();
	void applyMaterial(GLfloat*,GLfloat*,GLfloat*,GLfloat);
	void applyMaterial(GLfloat*,GLfloat*,GLfloat*,GLfloat*,GLfloat);
	void setObjPos(double,double,double);
	//ANimation
	virtual void checkIfFinished();
private:
	//Xrwma otan den xtypa t fws
	GLfloat *ambient_color;
	//to xrwma p diaxeetai
	GLfloat *diffuse_color;
	//GUalada se korufes p.x
	GLfloat *specular_color;

	//To Xrwma pou ekpempei
	GLfloat *emission_color;

	GLfloat shininess;
public:
	Object(double,double,double);

	int ID;

	virtual void view()=0;
	virtual void setPosition(double,double,double)=0;

	virtual void moveForward()=0; /*Moves to x, or z*/
	virtual void moveBackWard()=0; /*ROtates/ ,Update dir z and call moveFoward*/
	virtual void moveLeft()=0;	/*Rotate update dir x and call movefoward*/
	virtual void moveRight()=0;	/**/
	virtual void moveUp()=0;
	virtual void moveDown()=0;
	virtual void update_target()=0;

	double* getObjPosition();
	double* getTargetPosition();
	bool hasCollision(Object*);
	double *getDiretion();
	void setDirection(double*);
	void stopMoving();
	bool isOutOfBounds();
	virtual double getWidth();
	virtual double getXPos();
	//virtual void setXPos(double);
	virtual double getYPos();
	//virtual void setYPos(double);
	virtual double getZPos();
	//virtual void setZPos(double);
	virtual int getDir_z();
	virtual int getDir_y();
	virtual int getDir_x();
	bool isMoving();
	void print();
	virtual ~Object();
};

#endif /* SRC_OBJECT_H_ */

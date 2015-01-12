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
	float x_point,y_point,z_point;
	float x_target,y_target,z_target;
	float dir_z; /*1,-1*/
	float dir_x;
	float dir_y;
	float width;
	//Animations
	bool on_move;
	bool on_rot;
	bool on_jump;

	float target_rot_deg; /*movefowarrd:0,movrelft,right 90,270, move_back: 180*/
	float curr_rot_deg; /*Where  to start rotatiing Default =0*/
	float clock_rot;
	float motion;

	void applyMaterial();
	void applyMaterial(GLfloat*,GLfloat*,GLfloat*,GLfloat);
	void applyMaterial(GLfloat*,GLfloat*,GLfloat*,GLfloat*,GLfloat);
	void setObjPos(float,float,float);
	//ANimation
	void checkIfFinished();
	bool isMoving();
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
	Object(float,float,float);

	int ID;

	virtual void view()=0;
	virtual void setPosition(float,float,float)=0;

	virtual void moveForward()=0; /*Moves to x, or z*/
	virtual void moveBackWard()=0; /*ROtates/ ,Update dir z and call moveFoward*/
	virtual void moveLeft()=0;	/*Rotate update dir x and call movefoward*/
	virtual void moveRight()=0;	/**/
	virtual void moveUp()=0;
	virtual void moveDown()=0;
	virtual void update_target()=0;

	float* getObjPosition();
	float* getTargetPosition();
	bool hasCollision(Object*);
	float *getDiretion();
	void setDirection(float*);
	void stopMoving();
	bool isOutOfBounds();
	virtual float getWidth();
	virtual float getXPos();
	//virtual void setXPos(float);
	virtual float getYPos();
	//virtual void setYPos(float);
	virtual float getZPos();
	//virtual void setZPos(float);
	virtual int getDir_z();
	virtual int getDir_y();
	virtual int getDir_x();

	virtual ~Object();
};

#endif /* SRC_OBJECT_H_ */

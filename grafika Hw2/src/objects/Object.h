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

class Object {
protected:
	/*
	 *  For the glMaterial, it's usual to set the Ambient and Diffuse colours to
	 *    the natural colour of the object and to put the Specular colour to white.
	 *   The emission colour is generally black for objects that do not shine by their own light.
	 */
	float x_point,y_point,z_point;
	//Xrwma otan den xtypa t fws
	GLfloat *ambient_color;
	//to xrwma p diaxeetai
	GLfloat *diffuse_color;
	//GUalada se korufes p.x
	GLfloat *specular_color;
	//To Xrwma pou ekpempei
	GLfloat *emission_color;

	GLfloat shininess;

	void applyMaterial();
	void applyMaterial(GLfloat*,GLfloat*,GLfloat*,GLfloat);
	void applyMaterial(GLfloat*,GLfloat*,GLfloat*,GLfloat*,GLfloat);
public:
	Object(float,float,float);
	virtual void view()=0;
	virtual ~Object();
};

#endif /* SRC_OBJECT_H_ */

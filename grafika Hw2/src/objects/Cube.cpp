/*
 * Cube.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#include "Cube.h"

Cube::Cube(double width,double x,double y,double z,bool center): Object(x,y,z) {
	this->width = width;

/*	this->x=width/2+x_point;
	this->y=width/2+y_point;
	this->z=width/2+z_point;
*/
	this->field_center =center;
}


void Cube::setRandomColor(){
	this->color = new GLfloat[4];
	if(field_center==true){
		color[0]=1.0;
		color[2]=1.0;
		apothema=0;
	}
	else{
		int number=rand()%4;
		if(number==0){
			color[0]=1.0;
			apothema=2;
		}
		else if(number==1){
			color[2]=1.0;
			apothema=0;
		}
		else if(number==2){
			color[1]=1.0;
			apothema=3;
		}
		else
		{
			color[0]=1.0;
			color[1]=1.0;
			apothema=1;
		}
	}
	//ALpa
	color[3] = 1.0;
}

void Cube::createCube(double distanceX,double distanceY,double distanceZ){
	GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
	  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
	  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
	glBegin(GL_QUADS);
	// front face
	glColor3f(0.0,0.0,0.0);
	glNormal3fv(&n[0][0]);
	glVertex3f(width/2+distanceX,width/2+distanceY,width/2+distanceZ);
	glVertex3f(-width/2+distanceX,width/2+distanceY,width/2+distanceZ);
	glVertex3f(-width/2+distanceX,-width/2+distanceY,width/2+distanceZ);
	glVertex3f(width/2+distanceX,-width/2+distanceY,width/2+distanceZ);
	// left face
	glColor3f(0.0,0.0,0.0);
	glNormal3fv(&n[1][0]);
	glVertex3f(-width/2+distanceX,width/2+distanceY,width/2+distanceZ);
	glVertex3f(-width/2+distanceX,-width/2+distanceY,width/2+distanceZ);
	glVertex3f(-width/2+distanceX,-width/2+distanceY,-width/2+distanceZ);
	glVertex3f(-width/2+distanceX,width/2+distanceY,-width/2+distanceZ);
	// back face
	glColor3f(0.0,0.0,0.0);
	glNormal3fv(&n[2][0]);
	glVertex3f(width/2+distanceX,width/2+distanceY,-width/2+distanceZ);
	glVertex3f(-width/2+distanceX,width/2+distanceY,-width/2+distanceZ);
	glVertex3f(-width/2+distanceX,-width/2+distanceY,-width/2+distanceZ);
	glVertex3f(width/2+distanceX,-width/2+distanceY,-width/2+distanceZ);
	// right face
	glColor3f(0.0,0.0,0.0);
	glNormal3fv(&n[3][0]);
	glVertex3f(width/2+distanceX,width/2+distanceY,width/2+distanceZ);
	glVertex3f(width/2+distanceX,-width/2+distanceY,width/2+distanceZ);
	glVertex3f(width/2+distanceX,-width/2+distanceY,-width/2+distanceZ);
	glVertex3f(width/2+distanceX,width/2+distanceY,-width/2+distanceZ);
	// top face
	glColor3f(color[0],color[1],color[2]);
	glNormal3fv(&n[4][0]);
	glVertex3f(width/2+distanceX,width/2+distanceY,width/2+distanceZ);
	glVertex3f(-width/2+distanceX,width/2+distanceY,width/2+distanceZ);
	glVertex3f(-width/2+distanceX,width/2+distanceY,-width/2+distanceZ);
	glVertex3f(width/2+distanceX,width/2+distanceY,-width/2+distanceZ);
	// bottom face
	glColor3f(0.0,0.0,0.0);
	glNormal3fv(&n[5][0]);
	glVertex3f(width/2+distanceX,-width/2+distanceY,width/2+distanceZ);
	glVertex3f(-width/2+distanceX,-width/2+distanceY,width/2+distanceZ);
	glVertex3f(-width/2+distanceX,-width/2+distanceY,-width/2+distanceZ);
	glVertex3f(width/2+distanceX,-width/2+distanceY,-width/2+distanceZ);
glEnd();
}


Cube* Cube::getCenter(){
	if(this->field_center==true){
		return this;
	}
	return NULL;
}

void Cube::view(){
	this->checkIfFinished();
	if((on_move)){
		x_point += move_anim_frame*dir_x;
		z_point +=move_anim_frame*dir_z;
		y_point += move_anim_frame*dir_y;
	}
	glPushMatrix();
	glTranslatef(0,0,0.5);
	GLfloat *amb_color = new GLfloat[4]{0.1,0.1,0.1,1.0};//new GLfloat[4]{color[0]/2.0,color[1]/2.0,color[2]/2.0,1.0};
	applyMaterial(amb_color,color,new GLfloat[4]{1.0,1.0,1.0,1.0},50);
	createCube(x_point,y_point,z_point);
	glPopMatrix();
}

void Cube::setPosition(double x, double y, double z) {
	this->setObjPos(x,y,z);
}

void Cube::setColor(GLfloat* color) {
	this->color = color;
}

void Cube::update_target(){
	z_target = z_point+(char_step+gap_size*sizeOfCube)*dir_z;
	x_target = x_point+(char_step+gap_size*sizeOfCube)*dir_x;
	y_target = y_point+char_step*dir_y;
	this->x_target = round(x_target);
	this->y_target = round(y_target);
	this->z_target = round(z_target);
}

void Cube::moveForward(){
	if(on_move)
		return;
	x_target = x_point;
	y_target = y_point;
	z_target = z_point;
	update_target();

	on_move=true;
}

void Cube::moveBackWard(){
}

void Cube::moveLeft(){
}

void Cube::moveRight(){
}


void Cube::moveUp() {
}

void Cube::moveDown() {
	dir_x=0;
	dir_y=-1;
	dir_z=0;
	this->update_target();
	on_move = true;
}
void Cube::setApothema(int apothema){
	this->apothema=apothema;
}

int Cube::getApothema(){

}
bool Cube::isHidden() const {
	return hidden;
}

void Cube::hide() {
	this->hidden = true;
}

Cube::~Cube() {
	// TODO Auto-generated destructor stub
}

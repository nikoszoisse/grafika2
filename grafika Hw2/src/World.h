/*
 * World.h
 *
 *  Created on: Dec 15, 2014
 *      Author: aster
 */

#ifndef WORLD_H_
#define WORLD_H_
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "./objects/Object.h"
#include "./objects/Cube.h"
#include "./objects/Character.h"
#include "./objects/LightObject.h"



using namespace std;

class World {
private:
	//FIELDS
	Character *player;
	//static vector<Cube*> cubes;
	int grid_size;
	LightObject sun;
	//METHODS
	static void renderScene();
	static void reshapeScene(int,int);
public:
	World();
	void init(int argc,char** argv);
	void setGridSize(int gridSize);
	virtual ~World();
};
#endif /* WORLD_H_ */


extern Vector3D gCAR_POS;
extern float gSEGMENT_PROGRESS;
extern float gCAR_SPEED;
extern float gCAR_LAST_X;
#include "obstacle.hpp"

void Obstacle::draw() {
	switch(type){
		case CYLINDER: {
			glColor3f(YELLOW);
			glPushMatrix();{
				glTranslatef(shift,-0.29f,radius);
				glRotatef(-90, 1,0,0);
				drawSolidCylinder(quadric,radius,radius,height,8,1);
			}glPopMatrix();
		} break;
		case CUBE: {
			glColor3f(GREEN);
			glPushMatrix();{
				glTranslatef(shift,radius-0.29f,radius);
				glutSolidCube(height);
			}glPopMatrix();
		} break;
		case PYRAMID: {
			glColor3f(RED);
			glPushMatrix();{
				glTranslatef(shift,-0.29f,radius);
				drawSolidPyramid(radius,height);
			}glPopMatrix();
		} break;
	}
}

bool Obstacle::isCollision(){
	if( fabs(gCAR_POS.getX()-this->shift) <= CAR_WIDTH/2.0 + this->radius ){
		if( gSEGMENT_PROGRESS/(-2.0)-CAR_LENGTH < this->radius*2 )
			return true;
		if( gCAR_SPEED/2.0 >= CAR_LENGTH+(this->radius)*2 and fabs(gCAR_LAST_X-this->shift) <= CAR_WIDTH/2.0 + this->radius )
			return true;
	}
	return false;
}

float Obstacle::getShift(){ return shift; }
float Obstacle::getRadius(){ return radius; }
float Obstacle::getHeight(){ return height; }

void Obstacle::setShift( float newShift ){ this->shift = newShift; }
void Obstacle::setRadius( float newRadius ){ this->radius = newRadius; }
void Obstacle::setHeight( float newHeight ){ this->height = newHeight; }
















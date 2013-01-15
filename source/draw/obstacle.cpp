
extern Vector3D gCAR_POS;
extern float gSEGMENT_PROGRESS;
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
	return (
		gSEGMENT_PROGRESS/(-2.0)-CAR_LENGTH < this->radius*2
		and
		(
			( gCAR_POS.getX()+CAR_WIDTH/2.0 > this->shift-this->radius and this->shift+this->radius > gCAR_POS.getX()+CAR_WIDTH/2.0 )
			or
			( gCAR_POS.getX()-CAR_WIDTH/2.0 > this->shift-this->radius and this->shift+this->radius > gCAR_POS.getX()-CAR_WIDTH/2.0 )
			or
			( gCAR_POS.getX()-CAR_WIDTH/2.0 < this->shift-this->radius and this->shift+this->radius < gCAR_POS.getX()+CAR_WIDTH/2.0 )
		)
	)?true:false;
}

float Obstacle::getShift(){ return shift; }
float Obstacle::getRadius(){ return radius; }
float Obstacle::getHeight(){ return height; }

void Obstacle::setShift( float newShift ){ this->shift = newShift; }
void Obstacle::setRadius( float newRadius ){ this->radius = newRadius; }
void Obstacle::setHeight( float newHeight ){ this->height = newHeight; }

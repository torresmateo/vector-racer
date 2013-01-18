
extern Vector3D gCAR_POS;
extern float gSEGMENT_PROGRESS;
#include "blueSphere.hpp"

void BlueSphere::draw() {
	if( !triggered ){
		glColor3f(BLUE);
		glPushMatrix();{
			glTranslatef(shift,radius-0.29f,radius);
			glutSolidSphere(radius,8,8);
		}glPopMatrix();
	}
}

bool BlueSphere::isCollision(){
	if( fabs(gCAR_POS.getX()-this->shift) <= CAR_WIDTH/2.0 + this->radius ){
		if( gSEGMENT_PROGRESS/(-2.0)-CAR_LENGTH < this->radius*2 )
			return true;
		if( gCAR_SPEED/2.0 >= CAR_LENGTH+(this->radius)*2 and fabs(gCAR_LAST_X-this->shift) <= CAR_WIDTH/2.0 + this->radius )
			return true;
	}
	return false;
}

void BlueSphere::trigger(){
	if( triggered )
		return;
	gCAR_SPEED /= 1.1;
	triggered = true;
}

float BlueSphere::getShift(){ return shift; }
float BlueSphere::getRadius(){ return radius; }

void BlueSphere::setShift( float newShift ){ this->shift = newShift; }
void BlueSphere::setRadius( float newRadius ){ this->radius = newRadius; }

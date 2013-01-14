
extern Vector3D gCAR_POS;
extern float gSEGMENT_PROGRESS;
#include "blueSphere.hpp"

void BlueSphere::draw() {
	glColor3f(BLUE);
	glPushMatrix();{
		glTranslatef(shift,radius-0.29f,radius);
		glutSolidSphere(radius,8,8);
	}glPopMatrix();
}

bool BlueSphere::isCollision(){
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

float BlueSphere::getShift(){ return shift; }
float BlueSphere::getRadius(){ return radius; }

void BlueSphere::setShift( float newShift ){ this->shift = newShift; }
void BlueSphere::setRadius( float newRadius ){ this->radius = newRadius; }


extern Vector3D gCAR_POS;
extern float gSEGMENT_PROGRESS;
#include "whiteSphere.hpp"

void WhiteSphere::draw() {
	glColor3f(WHITE);
	glPushMatrix();{
		glTranslatef(shift,radius-0.29f,radius);
		glutSolidSphere(radius,8,8);
	}glPopMatrix();
}

bool WhiteSphere::isCollision(){
	return (
		gSEGMENT_PROGRESS/(-2.0)-CAR_LENGTH < this->radius*2
		and
		(
			( gCAR_POS.getX()+CAR_WIDTH/2.0 > this->shift-this->radius and this->shift+this->radius > gCAR_POS.getX()+CAR_WIDTH/2.0 )
			or
			( gCAR_POS.getX()-CAR_WIDTH/2.0 > this->shift-this->radius and this->shift+this->radius > gCAR_POS.getX()-CAR_WIDTH/2.0 )
		)
	)?true:false;
}

float WhiteSphere::getShift(){ return shift; }
float WhiteSphere::getRadius(){ return radius; }

void WhiteSphere::setShift( float newShift ){ this->shift = newShift; }
void WhiteSphere::setRadius( float newRadius ){ this->radius = newRadius; }
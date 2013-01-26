
extern Vector3D gCAR_POS;
extern float gSEGMENT_PROGRESS;
extern int gCAR_HEALTH;

#include "whiteSphere.hpp"

void WhiteSphere::draw() {
	if( !triggered ){
		glColor3f(WHITE);
		glPushMatrix();{
			glTranslatef(shift,radius-0.29f,radius);
			glutSolidSphere(radius,8,8);
		}glPopMatrix();
	}
}

bool WhiteSphere::isCollision(){
	if( fabs(gCAR_POS.getX()-this->shift) <= CAR_WIDTH/2.0 + this->radius ){
		if( gSEGMENT_PROGRESS/(-2.0)-CAR_LENGTH < this->radius*2 )
			return true;
		if( gCAR_SPEED/2.0 >= CAR_LENGTH+(this->radius)*2 and fabs(gCAR_LAST_X-this->shift) <= CAR_WIDTH/2.0 + this->radius )
			return true;
	}
	return false;
}

void WhiteSphere::trigger(){
	if( triggered )
		return;
	
	if( !gCAR_GHOST ){
		if(gCAR_HEALTH<3)
			gCAR_HEALTH++;
		gSOUND_ENGINE->play2D("../media/white-sphere.wav");
		triggered = true;
	}
}

float WhiteSphere::getShift(){ return shift; }
float WhiteSphere::getRadius(){ return radius; }

void WhiteSphere::setShift( float newShift ){ this->shift = newShift; }
void WhiteSphere::setRadius( float newRadius ){ this->radius = newRadius; }
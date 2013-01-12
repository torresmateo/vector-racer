
#include "whiteSphere.hpp"


void WhiteSphere::draw() {
	glColor3f(WHITE);
	glPushMatrix();{
		glTranslatef(shift,-0.25f,0.25f);
		glutSolidSphere(radius,8,8);
	}glPopMatrix();
}
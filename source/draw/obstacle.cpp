
extern Vector3D gCAR_POS;
extern float gSEGMENT_PROGRESS;
extern float gCAR_SPEED;
extern float gCAR_LAST_X;
extern int gCAR_HEALTH;
extern int gCAR_GHOST;

#include "obstacle.hpp"

void drawTexturedCube( float edgeLength ){
	edgeLength /= 2;
	glPolygonMode(GL_BACK, GL_LINE);//GL_LINE
	glPolygonMode(GL_FRONT, GL_FILL);//GL_FILL
	
	glBegin(GL_QUADS);
        glVertex3f( +edgeLength, -edgeLength, +edgeLength);
        glVertex3f( +edgeLength, +edgeLength, +edgeLength);
        glVertex3f( -edgeLength, +edgeLength, +edgeLength);
        glVertex3f( -edgeLength, -edgeLength, +edgeLength);
    glEnd();
	
	glBegin(GL_QUADS);
        glVertex3f( +edgeLength, -edgeLength, -edgeLength);
        glVertex3f( +edgeLength, +edgeLength, -edgeLength);
        glVertex3f( +edgeLength, +edgeLength, +edgeLength);
        glVertex3f( +edgeLength, -edgeLength, +edgeLength);
    glEnd();
	
	glBegin(GL_QUADS);
        glVertex3f( -edgeLength, -edgeLength, -edgeLength);
        glVertex3f( -edgeLength, +edgeLength, -edgeLength);
        glVertex3f( +edgeLength, +edgeLength, -edgeLength);
        glVertex3f( +edgeLength, -edgeLength, -edgeLength);
    glEnd();
	
	glBegin(GL_QUADS);
        glVertex3f( -edgeLength, -edgeLength, +edgeLength);
        glVertex3f( -edgeLength, +edgeLength, +edgeLength);
        glVertex3f( -edgeLength, +edgeLength, -edgeLength);
        glVertex3f( -edgeLength, -edgeLength, -edgeLength);
    glEnd();
	
	glBegin(GL_QUADS);
        glVertex3f( -edgeLength, +edgeLength, -edgeLength );
        glVertex3f( -edgeLength, +edgeLength, +edgeLength );
        glVertex3f( +edgeLength, +edgeLength, +edgeLength );
        glVertex3f( +edgeLength, +edgeLength, -edgeLength );
    glEnd();
	
	glBegin(GL_QUADS);
        glVertex3f( +edgeLength, -edgeLength, -edgeLength );
        glVertex3f( +edgeLength, -edgeLength, +edgeLength );
        glVertex3f( -edgeLength, -edgeLength, +edgeLength );
        glVertex3f( -edgeLength, -edgeLength, -edgeLength );
    glEnd();
	
	glPolygonMode(GL_BACK, GL_FILL);//GL_LINE
	glPolygonMode(GL_FRONT, GL_FILL);//GL_FILL
}

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
				drawTexturedCube(height);
			}glPopMatrix();
		} break;
		case PYRAMID: {
			glColor3f(RED);
			glPushMatrix();{
				glTranslatef(shift,-0.29f,radius);
				drawWirePyramid(radius,height);
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

void Obstacle::trigger(){
	if(triggered)
		return;
	
	if( !gCAR_GHOST ){
		if( gCAR_HEALTH > 0 )
			gCAR_HEALTH--;
			
		if( gCAR_HEALTH > 0 )
			carGhostHandler(0);
	}
		
	triggered = true;
}

float Obstacle::getShift(){ return shift; }
float Obstacle::getRadius(){ return radius; }
float Obstacle::getHeight(){ return height; }

void Obstacle::setShift( float newShift ){ this->shift = newShift; }
void Obstacle::setRadius( float newRadius ){ this->radius = newRadius; }
void Obstacle::setHeight( float newHeight ){ this->height = newHeight; }
















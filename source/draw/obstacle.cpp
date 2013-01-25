
extern Vector3D gCAR_POS;
extern float gSEGMENT_PROGRESS;
extern float gCAR_SPEED;
extern float gCAR_LAST_X;
extern int gCAR_HEALTH;
extern int gCAR_GHOST;
extern unsigned int gCUBE_TEXTURE;
extern float gDIFFUSE[4];
extern float gAMBIENT[4];
extern float gSPECULAR[4];
extern float gSHININESS;

#include "obstacle.hpp"

void drawTexturedCube( float edgeLength ){
	edgeLength /= 2;
	glPolygonMode(GL_BACK, GL_LINE);//GL_LINE
	glPolygonMode(GL_FRONT, GL_FILL);//GL_FILL
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,gCUBE_TEXTURE);
	
	
	
	
	glBegin(GL_QUADS);//cara con normal +z
		glTexCoord2f(1,0);
		glVertex3f( +edgeLength, -edgeLength, +edgeLength);
		glTexCoord2f(1,1);
		glVertex3f( +edgeLength, +edgeLength, +edgeLength);
		glTexCoord2f(0,1);
		glVertex3f( -edgeLength, +edgeLength, +edgeLength);
		glTexCoord2f(0,0);
		glVertex3f( -edgeLength, -edgeLength, +edgeLength);
    glEnd();
	
	glBegin(GL_QUADS);//cara con normal +x
		glTexCoord2f(1,0);
		glVertex3f( +edgeLength, -edgeLength, -edgeLength);
		glTexCoord2f(1,1);
		glVertex3f( +edgeLength, +edgeLength, -edgeLength);
		glTexCoord2f(0,1);
		glVertex3f( +edgeLength, +edgeLength, +edgeLength);
		glTexCoord2f(0,0);
		glVertex3f( +edgeLength, -edgeLength, +edgeLength);
    glEnd();
	
	glBegin(GL_QUADS);//cara con normal -z
		glTexCoord2f(0,0);
		glVertex3f( -edgeLength, -edgeLength, -edgeLength);
		glTexCoord2f(0,1);
		glVertex3f( -edgeLength, +edgeLength, -edgeLength);
		glTexCoord2f(1,1);
		glVertex3f( +edgeLength, +edgeLength, -edgeLength);
		glTexCoord2f(1,0);
		glVertex3f( +edgeLength, -edgeLength, -edgeLength);
    glEnd();
	
	glBegin(GL_QUADS);//cara con normal -x
		glTexCoord2f(1,0);
		glVertex3f( -edgeLength, -edgeLength, +edgeLength);
		glTexCoord2f(1,1);
		glVertex3f( -edgeLength, +edgeLength, +edgeLength);
		glTexCoord2f(0,1);
		glVertex3f( -edgeLength, +edgeLength, -edgeLength);
		glTexCoord2f(0,0);
		glVertex3f( -edgeLength, -edgeLength, -edgeLength);
    glEnd();
	
	glBegin(GL_QUADS);//cara con normal +y
		glTexCoord2f(1,0);
		glVertex3f( -edgeLength, +edgeLength, -edgeLength );
		glTexCoord2f(1,1);
		glVertex3f( -edgeLength, +edgeLength, +edgeLength );
		glTexCoord2f(0,1);
		glVertex3f( +edgeLength, +edgeLength, +edgeLength );
		glTexCoord2f(0,0);
		glVertex3f( +edgeLength, +edgeLength, -edgeLength );
    glEnd();
	
	glBegin(GL_QUADS);//cara con normal -y
		glTexCoord2f(1,0);
		glVertex3f( +edgeLength, -edgeLength, -edgeLength );
		glTexCoord2f(1,1);
		glVertex3f( +edgeLength, -edgeLength, +edgeLength );
		glTexCoord2f(0,1);
		glVertex3f( -edgeLength, -edgeLength, +edgeLength );
		glTexCoord2f(0,0);
		glVertex3f( -edgeLength, -edgeLength, -edgeLength );
    glEnd();
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glPolygonMode(GL_BACK, GL_FILL);//GL_LINE
	glPolygonMode(GL_FRONT, GL_FILL);//GL_FILL
}

void Obstacle::draw() {


	glMaterialfv(GL_FRONT,GL_DIFFUSE,gDIFFUSE);
//	glMaterialfv(GL_FRONT,GL_AMBIENT,gAMBIENT);
	glMaterialfv(GL_FRONT,GL_SPECULAR,gSPECULAR);
	glMaterialf(GL_FRONT,GL_SHININESS,0.0);

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

















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
extern ISoundEngine* gSOUND_ENGINE;

#include "obstacle.hpp"

//dibuja un cubo con textura con aristas de longitud "edgeLength"
void drawTexturedCube( float edgeLength ){
    //dividimos la longitud por la mitad para dibujar centrado el cubo
	edgeLength /= 2;
    
    //modificamos el PolygonMode de tal forma a que el frente sea relleno y el interior no
	glPolygonMode(GL_BACK, GL_LINE);//GL_LINE
	glPolygonMode(GL_FRONT, GL_FILL);//GL_FILL
	
    //habilitamos la luz
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    
    //habilitamos las texturas
	glEnable(GL_TEXTURE_2D);
    
    //hacemos el binding de texturas correspondiente
	glBindTexture(GL_TEXTURE_2D,gCUBE_TEXTURE);
	
    //dibujamos las caras

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
	
    //deshabilitamos la textura y la iluminación
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

    //resetamos el PolygonMode
	glPolygonMode(GL_BACK, GL_FILL);//GL_LINE
	glPolygonMode(GL_FRONT, GL_FILL);//GL_FILL
}

//dibuja los obstaculos
void Obstacle::draw() {

	switch(type){//dependiendo del tipo 

        //dibujamos el cilindro amarillo
		case CYLINDER: {
            //seteamos el color
			glColor3f(YELLOW);
			glPushMatrix();{
			
			    //habilitamos la luz
				glEnable(GL_LIGHTING);
			
				glTranslatef(shift,-0.29f,radius);
				glRotatef(-90, 1,0,0);
				
			    //configuramos los valores de la luz
				GLfloat light_ambient[] = { 1.75, 1.75, 0.0, 1.0 };
				GLfloat light_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
				GLfloat light_specular[] = { 1.0, 1.0, 0.0, 1.0 };
				GLfloat light_position[] = { -10.0, -10.0, 10.0, -10.5 };
				glLightfv (GL_LIGHT3, GL_AMBIENT, light_ambient);
				glLightfv (GL_LIGHT3, GL_DIFFUSE, light_diffuse);
				glLightfv (GL_LIGHT3, GL_SPECULAR, light_specular);
				glLightfv (GL_LIGHT3, GL_POSITION, light_position);
				
                //habilitamos la luz que acabamos de configurar
				glEnable(GL_LIGHT3);

				//configuración del material del cilindro
				float diffuse[4]={0.5f,0.55f,0.0f,1.0f};
				float ambient[4]={0.3f,0.3f,0.0f,1.0f};
				float specular[4]={0.0f,0.0f,0.0f,1.0f};
				float shininess=0.5f;
				glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
				glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
				glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
				glMaterialf(GL_FRONT,GL_SHININESS,shininess);

				//dibujamos un cilindro
				drawSolidCylinder(quadric,radius,radius,height,8,1);
                
                //reseteamos la configuración de materiales
				resetMaterials();
                
                //deshabilitamos las luces
				glDisable(GL_LIGHT3);
				glDisable(GL_LIGHTING);

			}glPopMatrix();
		} break;
        //dibujamos el cubo verde
		case CUBE: {
            //seteamos el color (irrelevante por la textura)
			glColor3f(GREEN);
			glPushMatrix();{
				glTranslatef(shift,radius-0.29f,radius);
                //dibujamos un cubo
				drawTexturedCube(height);
			}glPopMatrix();
		} break;
        //dibujamos la piramide roja
		case PYRAMID: {
            //seteamos el color
			glColor3f(RED);
			glPushMatrix();{
				glTranslatef(shift,-0.29f,radius);
                //dibujamos una pirámide
				drawWirePyramid(radius,height);
			}glPopMatrix();
		} break;
	}
}

//detección de colisiones
bool Obstacle::isCollision(){
    //si coinciden las áreas horizontalmente
	if( fabs(gCAR_POS.getX()-this->shift) <= CAR_WIDTH/2.0 + this->radius ){
        //si coinciden la áreas en profundidad
		if( gSEGMENT_PROGRESS/(-2.0)-CAR_LENGTH < this->radius*2 )
			return true;
        //si las áreas se traspasaron entre el muestreo anterior y el actual (corrección de discretización)
		if( gCAR_SPEED/2.0 >= CAR_LENGTH+(this->radius)*2 and fabs(gCAR_LAST_X-this->shift) <= CAR_WIDTH/2.0 + this->radius )
			return true;
	}
    //si no se dió alguno de los casos anteriores, no hubo colisión
	return false;
}

//disparador de eventos
void Obstacle::trigger(){
    //si el evento del obstáculo ya fue disparado, ignoramos el evento
	if(triggered)
		return;
    
    //si no estamos en el modo "fantasma"
	if( !gCAR_GHOST ){
        //si le queda vida a la nave
		if( gCAR_HEALTH > 0 ){
            //reproducimos el sonido de impacto
			gSOUND_ENGINE->play2D("../media/impact.wav");
            //restamos una vida al auto
			gCAR_HEALTH--;
            //si la nave sigue con vida, llamamos al estado Ghost
			if( gCAR_HEALTH > 0 )
				carGhostHandler(0);
		}
	}

	//el evento fue triggereado
	triggered = true;
}

//getters
float Obstacle::getShift(){ return shift; }
float Obstacle::getRadius(){ return radius; }
float Obstacle::getHeight(){ return height; }

//setters
void Obstacle::setShift( float newShift ){ this->shift = newShift; }
void Obstacle::setRadius( float newRadius ){ this->radius = newRadius; }
void Obstacle::setHeight( float newHeight ){ this->height = newHeight; }
















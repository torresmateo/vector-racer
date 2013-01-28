
extern Vector3D gCAR_POS;
extern float gSEGMENT_PROGRESS;
extern int gCAR_HEALTH;

#include "whiteSphere.hpp"

//implementación de la clase WhiteSphere

//dibuja la esfera blanca
void WhiteSphere::draw() {
	//si el evento de colisión asociado a esta esfera aún no fue disparado
    if( !triggered ){
        //establecemos el color blanco
		glColor3f(WHITE);
		glPushMatrix();{
			glTranslatef(shift,radius-0.29f,radius);
            //dibujamos la esfera
			glutSolidSphere(radius,8,8);
		}glPopMatrix();
	}
}

//detección de colisión con la esfera
bool WhiteSphere::isCollision(){
    //si las áreas coinciden horizontalmente 
	if( fabs(gCAR_POS.getX()-this->shift) <= CAR_WIDTH/2.0 + this->radius ){
        //si las áreas coinciden en profundidad
		if( gSEGMENT_PROGRESS/(-2.0)-CAR_LENGTH < this->radius*2 )
			return true;
        //si las áreas se traspasaron entre el muestreo anterior y el actual (corrección de discretización)
		if( gCAR_SPEED/2.0 >= CAR_LENGTH+(this->radius)*2 and fabs(gCAR_LAST_X-this->shift) <= CAR_WIDTH/2.0 + this->radius )
			return true;
	}
    //si no se dió alguno de los casos anteriores, no hubo colisión
	return false;
}

//evento de colisión con una esfera blanca
void WhiteSphere::trigger(){
    //si el evento de colisión con la esfera ya ha sido disparado, ignoramos el evento
	if( triggered )
		return;
	
    //si no estamos en el modo post colisión, respondemos ante el evento
	if( !gCAR_GHOST ){
        //si la cantidad de vidas de la nave es menor al máximo, se agrega una vida
		if(gCAR_HEALTH<3)
			gCAR_HEALTH++;
        //se reproduce el sonido de colisión con la esfera blanca
		gSOUND_ENGINE->play2D("../media/white-sphere.wav");
        //el evento de esta esfera fue disparado
		triggered = true;
	}
}

//getters
float WhiteSphere::getShift(){ return shift; }
float WhiteSphere::getRadius(){ return radius; }

//setters
void WhiteSphere::setShift( float newShift ){ this->shift = newShift; }
void WhiteSphere::setRadius( float newRadius ){ this->radius = newRadius; }


extern Vector3D gCAR_POS;
extern float gSEGMENT_PROGRESS;
#include "blueSphere.hpp"
//implementación de la clase BlueSphere

//función de dibujado de la esfera
void BlueSphere::draw() {
    //si no fue utilizado el evento de esta esfera, la dibujamos
	if( !triggered ){
        //seteamos el color azúl
		glColor3f(BLUE);
		glPushMatrix();{
			glTranslatef(shift,radius-0.29f,radius);
            //dibujamos una esfera
			glutSolidSphere(radius,8,8);
		}glPopMatrix();
	}
}

//detección de colisión
bool BlueSphere::isCollision(){
    //si las areas coinciden de forma horizontal
	if( fabs(gCAR_POS.getX()-this->shift) <= CAR_WIDTH/2.0 + this->radius ){
        //si las areas coinciden en profundidad
		if( gSEGMENT_PROGRESS/(-2.0)-CAR_LENGTH < this->radius*2 )
			return true;
        //si las áreas se atravesaron entre el instante actual y el último instante calculado (corrección de la discretización)
		if( gCAR_SPEED/2.0 >= CAR_LENGTH+(this->radius)*2 and fabs(gCAR_LAST_X-this->shift) <= CAR_WIDTH/2.0 + this->radius )
			return true;
	}
    //si ninguno de los casos anteriores se cumple, no hubo colisión
	return false;
}

//acción realizada al colisionar con la esfera
void BlueSphere::trigger(){
    //si ya fue utilizado este evento, lo ignoramos
	if( triggered )
		return;
	
    //si no estamos en el estado post colisión
	if( !gCAR_GHOST ){
        //reproducimos el sonido de colisión con la esfera azúl
		gSOUND_ENGINE->play2D("../media/blue-sphere.wav");
        //reducimos la velocidad en un factor de 1.1
		gCAR_SPEED /= 1.1;
        //este evento ya fué disparado
		triggered = true;
	}
}

//getters
float BlueSphere::getShift(){ return shift; }
float BlueSphere::getRadius(){ return radius; }

//setters
void BlueSphere::setShift( float newShift ){ this->shift = newShift; }
void BlueSphere::setRadius( float newRadius ){ this->radius = newRadius; }

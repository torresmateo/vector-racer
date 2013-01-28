#include "pathSection.hpp"
//implementación de la clase PathSection



//seters
void PathSection::setRadius( float newRadius ){ this->radius = newRadius; }
void PathSection::setNumberOfSegments(int newNumberOfSegments){ this->numberOfSegments = newNumberOfSegments; }
		

void PathSection::setPositionIni( Vector3D newPosition ){ this->positionIni = newPosition; }
void PathSection::setNormalIni( Vector3D newNormal ){ this->normalIni = newNormal; }

void PathSection::setPositionEnd( Vector3D newPosition ){ this->positionEnd = newPosition; }
void PathSection::setNormalEnd( Vector3D newNormal ){ this->normalEnd = newNormal; }

//geters
float PathSection::getRadius(){ return this->radius; }
int PathSection::getNumberOfSegments(){ return this->numberOfSegments; }
		

Vector3D PathSection::getPositionIni(){ return this->positionIni; }
Vector3D PathSection::getNormalIni(){ return this->normalIni; }

Vector3D PathSection::getPositionEnd(){ return this->positionEnd; }
Vector3D PathSection::getNormalEnd(){ return this->normalEnd; }





//utils

//retorna true si hay algún obstáculo en el segmento i
bool PathSection::thereIsObstacle(int i) {
	return obstacles[i]? true : false;
}

//retorna true si hay una esfera azúl en el segmento i
bool PathSection::thereIsBlueSphere(int i) {
	return blueSpheres[i]? true : false;
}

//retorna true si hay una esfera blanca en el segmento i
bool PathSection::thereIsWhiteSphere(int i) {
	return whiteSpheres[i]? true : false;
}

//retorna true si hay una esfera blanca en el segmento i
bool PathSection::thereIsFuchsiaSphere(int i) {
	return fuchsiaSpheres[i]? true : false;
}

//retorna el obstáculo del segmento i
Obstacle* PathSection::getObstacle(int i) {
	return obstacles[i];
}

//retorna la esfera azúl del segmento i
BlueSphere* PathSection::getBlueSphere(int i) {
	return blueSpheres[i];
}

//retorna la esfera blanca del segmento i
WhiteSphere* PathSection::getWhiteSphere(int i) {
	return whiteSpheres[i];
}

//retorna la esfera fucsia del segmento i
FuchsiaSphere* PathSection::getFuchsiaSphere(int i) {
	return fuchsiaSpheres[i];
}

//borra los obstáculos y las esferas de la sección
void PathSection::deleteItems(){
	for(int i = 0; i<84; i++){
		delete obstacles[i];
		delete blueSpheres[i];
		delete whiteSpheres[i];
		delete fuchsiaSpheres[i];
		obstacles[i] = NULL;
		blueSpheres[i] = NULL;
		whiteSpheres[i] = NULL;
		fuchsiaSpheres[i] = NULL;
	}
}

//genera obstáculos y esferas en la sección
void PathSection::createItems(){
	for(int i = 0; i<84; i++){
        //agregamos los obstáculos
		if(rand()%100 < 35)
			obstacles[i] = new Obstacle;
			
        //agregamos las esferas azules
		if(rand()%1000 < 3){
			if( obstacles[i] )
				blueSpheres[i] = new BlueSphere(obstacles[i]->getShift(),obstacles[i]->getRadius());
			else
				blueSpheres[i] = new BlueSphere();
		}
			
        //agregamos las esferas fucsia
		if(rand()%1000 < 1000){
			if( obstacles[i] )
				fuchsiaSpheres[i] = new FuchsiaSphere(obstacles[i]->getShift(),obstacles[i]->getRadius());
			else
				fuchsiaSpheres[i] = new FuchsiaSphere();
		}
			
        //agregamos las esferas blancas
		if(rand()%100 < 2){
			if( obstacles[i] )
				whiteSpheres[i] = new WhiteSphere(obstacles[i]->getShift(),obstacles[i]->getRadius());
			else
				whiteSpheres[i] = new WhiteSphere();
		}
	}
}

//genera obstáculos y esferas en la sección, ignorando los primeros "segmentsLeftOut" segmentos
void PathSection::createItems( int segmentsLeftOut ){
	for(int i = segmentsLeftOut; i<84; i++){
		if(rand()%100 < 35)
			obstacles[i] = new Obstacle;
			
		if(rand()%1000 < 3){
			if( obstacles[i] )
				blueSpheres[i] = new BlueSphere(obstacles[i]->getShift(),obstacles[i]->getRadius());
			else
				blueSpheres[i] = new BlueSphere();
		}
			
        //agregamos las esferas fucsia
		if(rand()%1000 < 1000){
			if( obstacles[i] )
				fuchsiaSpheres[i] = new FuchsiaSphere(obstacles[i]->getShift(),obstacles[i]->getRadius());
			else
				fuchsiaSpheres[i] = new FuchsiaSphere();
		}
			
		if(rand()%100 < 2){
			if( obstacles[i] )
				whiteSpheres[i] = new WhiteSphere(obstacles[i]->getShift(),obstacles[i]->getRadius());
			else
				whiteSpheres[i] = new WhiteSphere();
		}
	}
}

//regenera los obstáculos y esferas de la sección
void PathSection::resetItems(){
	this->deleteItems();
	this->createItems();
}

//regenera los obstáculos y esferas de la sección, ignorando los primeros "segmentsLeftOut" segmentos
void PathSection::resetItems( int segmentsLeftOut ){
	this->deleteItems();
	this->createItems(segmentsLeftOut);
}














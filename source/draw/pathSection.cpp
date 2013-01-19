#include "pathSection.hpp"



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

bool PathSection::thereIsObstacle(int i) {
	return obstacles[i]? true : false;
}

bool PathSection::thereIsBlueSphere(int i) {
	return blueSpheres[i]? true : false;
}

bool PathSection::thereIsWhiteSphere(int i) {
	return whiteSpheres[i]? true : false;
}

Obstacle* PathSection::getObstacle(int i) {
	return obstacles[i];
}

BlueSphere* PathSection::getBlueSphere(int i) {
	return blueSpheres[i];
}

WhiteSphere* PathSection::getWhiteSphere(int i) {
	return whiteSpheres[i];
}


Vector3D PathSection::getPointAtDegree(Vector3D axis, Vector3D orthogonal1, Vector3D orthogonal2, float degree){
	float theta = degree*PI/180.0f;
	GLfloat x = axis.getX() + radius*cos(theta)*orthogonal1.getX() + radius*sin(theta)*orthogonal2.getX();
	GLfloat y = axis.getY() + radius*cos(theta)*orthogonal1.getY() + radius*sin(theta)*orthogonal2.getY();
	GLfloat z = axis.getZ() + radius*cos(theta)*orthogonal1.getZ() + radius*sin(theta)*orthogonal2.getZ();
	return Vector3D(x, y, z);
}

void PathSection::deleteItems(){
	for(int i = 0; i<84; i++){
		delete obstacles[i];
		delete blueSpheres[i];
		delete whiteSpheres[i];
		obstacles[i] = NULL;
		blueSpheres[i] = NULL;
		whiteSpheres[i] = NULL;
	}
}

void PathSection::createItems(){
	for(int i = 0; i<84; i++){
		if(rand()%100 < 35)
			obstacles[i] = new Obstacle;
			
		if(rand()%1000 < 3){
			if( obstacles[i] )
				blueSpheres[i] = new BlueSphere(obstacles[i]->getShift(),obstacles[i]->getRadius());
			else
				blueSpheres[i] = new BlueSphere();
		}
			
		if(rand()%100 < 2){
			if( obstacles[i] )
				whiteSpheres[i] = new WhiteSphere(obstacles[i]->getShift(),obstacles[i]->getRadius());
			else
				whiteSpheres[i] = new WhiteSphere();
		}
	}
}

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
			
		if(rand()%100 < 2){
			if( obstacles[i] )
				whiteSpheres[i] = new WhiteSphere(obstacles[i]->getShift(),obstacles[i]->getRadius());
			else
				whiteSpheres[i] = new WhiteSphere();
		}
	}
}

void PathSection::resetItems(){
	this->deleteItems();
	this->createItems();
}

void PathSection::resetItems( int segmentsLeftOut ){
	this->deleteItems();
	this->createItems(segmentsLeftOut);
}














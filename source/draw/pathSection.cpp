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




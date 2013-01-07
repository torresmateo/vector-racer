#include "pathSection.hpp"



//seters
void PathSection::setRadius( float newRadius ){ this->radius = newRadius; }

void PathSection::setPositionIni( Vector3D newPosition ){ this->positionIni = newPosition; }
void PathSection::setNormalIni( Vector3D newNormal ){ this->normalIni = newNormal; }

void PathSection::setPositionEnd( Vector3D newPosition ){ this->positionEnd = newPosition; }
void PathSection::setNormalEnd( Vector3D newNormal ){ this->normalEnd = newNormal; }

//geters
float PathSection::getRadius(){ return this->radius; }

Vector3D PathSection::getPositionIni(){ return this->positionIni; }
Vector3D PathSection::getOrientationIni(){ return this->normalIni; }

Vector3D PathSection::getPositionEnd(){ return this->positionEnd; }
Vector3D PathSection::getOrientationEnd(){ return this->normalEnd; }





//utils

void PathSection::updateOrthogonalVectorsIni(){
	aIni = normalIni.getNormalizedVector().getUnitaryPerpendicularVector();
	bIni = Vector3D::crossMultiply(normalIni.getNormalizedVector(),aIni).getNormalizedVector();
}
void PathSection::updateOrthogonalVectorsEnd(){
	aEnd = normalEnd.getNormalizedVector().getUnitaryPerpendicularVector();
	bEnd = Vector3D::crossMultiply(normalIni.getNormalizedVector(),aEnd).getNormalizedVector();
}

void PathSection::updateOrthogonalVectors(){
	this->updateOrthogonalVectorsIni();
	this->updateOrthogonalVectorsEnd();
}


Vector3D PathSection::getPointAtDegree(Vector3D axis, Vector3D orthogonal1, Vector3D orthogonal2, float degree){
	float theta = degree*PI/180.0f;
	GLfloat x = axis.getX() + radius*cos(theta)*orthogonal1.getX() + radius*sin(theta)*orthogonal2.getX();
	GLfloat y = axis.getY() + radius*cos(theta)*orthogonal1.getY() + radius*sin(theta)*orthogonal2.getY();
	GLfloat z = axis.getZ() + radius*cos(theta)*orthogonal1.getZ() + radius*sin(theta)*orthogonal2.getZ();
	return Vector3D(x, y, z);
}

Vector3D PathSection::getPointAtDegreeIni(float degree){
	return getPointAtDegree(normalIni, aIni, bIni, degree);
}

Vector3D PathSection::getPointAtDegreeEnd(float degree){
	return getPointAtDegree(normalEnd, aEnd, bEnd, degree);
}


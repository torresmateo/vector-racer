#include "pathSection.hpp"



//seters
void PathSection::setRadius( Vector3D newRadius ){ this->radius = newRadius; }

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

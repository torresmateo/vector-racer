#include "pathSection.hpp"



//seters
void PathSection::setPositionIni( Vector3D newPosition ){ this->positionIni = newPosition; }
void PathSection::setNormalIni( Vector3D newNormal ){ this->normalIni = newNormal; }

void PathSection::setPositionFin( Vector3D newPosition ){ this->positionFin = newPosition; }
void PathSection::setNormalFin( Vector3D newNormal ){ this->normalFin = newNormal; }

//geters
Vector3D PathSection::getPositionIni(){ return this->positionIni; }
Vector3D PathSection::getOrientationIni(){ return this->normalIni; }

Vector3D PathSection::getPositionFin(){ return this->positionFin; }
Vector3D PathSection::getOrientationFin(){ return this->normalFin; }





//utils

void PathSection::updateOrthogonalVectorsIni(){
	aIni = normalIni.getNormalizedVector().getUnitaryPerpendicularVector();
	bIni = Vector3D::crossMultiply(normalIni.getNormalizedVector(),aIni).getNormalizedVector();
}
void PathSection::updateOrthogonalVectorsFin(){
	aFin = normalFin.getNormalizedVector().getUnitaryPerpendicularVector();
	bFin = Vector3D::crossMultiply(normalIni.getNormalizedVector(),aFin).getNormalizedVector();
}

void PathSection::updateOrthogonalVectors(){
	this->updateOrthogonalVectorsIni();
	this->updateOrthogonalVectorsFin();
}

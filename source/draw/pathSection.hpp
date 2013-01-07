#ifndef PATH_SECTION_H
#define PATH_SECTION_H
class PathSection {
	
	Vector3D positionIni;
	Vector3D normalIni;
	Vector3D aIni;				//vector perpendicular a normalIni
	Vector3D bIni;				//vector perpendicular a normalIni y aIni 
	
	//los vectores Fin asumen que el origen esta centrado en positionIni
	Vector3D positionFin;		
	Vector3D normalFin;
	Vector3D aFin;				//vector perpendicular a normalFin
	Vector3D bFin;				//vector perpendicular a normalFin y aFin
	
	public:
	
		//constructors
		
		PathSection() {
			positionIni = Vector3D(0.0f,0.0f,0.0f);
			normalIni = Vector3D(0.0f,0.0f,1.0f);;
			
			positionFin = Vector3D(0.0f,0.0f,1.0f);
			normalFin = Vector3D(0.0f,0.0f,1.0f);;
			
			this->updateOrthogonalVectors();
		}
		
		PathSection( Vector3D positionIni, Vector3D normalIni, Vector3D positionFin, Vector3D normalFin ) {
			this->positionIni = positionIni;
			this->normalIni = normalIni;
			this->positionFin = positionIni;
			this->normalFin = normalIni;

			this->updateOrthogonalVectors();
		}
		
		//seters
		void setPositionIni( Vector3D newPosition );
		void setNormalIni( Vector3D newOrientation );
		
		void setPositionFin( Vector3D newPosition );
		void setNormalFin( Vector3D newOrientation );
		
		//geters
		Vector3D getPositionIni();
		Vector3D getOrientationIni();
		
		Vector3D getPositionFin();
		Vector3D getOrientationFin();
		
		//utils
		void updateOrthogonalVectors();
		void updateOrthogonalVectorsIni();
		void updateOrthogonalVectorsFin();
		
		/*
		getPointAtDegree(Vector3D axis, float degree){
			float radian = degree*PI/180.0f;
			
		}
		
		Vector3D getPointAtDegreeIni(float degree){
			return getPointAtDegree(normalIni);
		}*/
};
#endif

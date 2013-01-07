#ifndef PATH_SECTION_H
#define PATH_SECTION_H
class PathSection {
	
	float radius;
	
	Vector3D positionIni;
	Vector3D normalIni;
	Vector3D aIni;				//vector perpendicular a normalIni
	Vector3D bIni;				//vector perpendicular a normalIni y aIni 
	
	//los vectores End asumen que el origen esta centrado en positionIni
	Vector3D positionEnd;		
	Vector3D normalEnd;
	Vector3D aEnd;				//vector perpendicular a normalEnd
	Vector3D bEnd;				//vector perpendicular a normalEnd y aEnd
	
	public:
	
		//constructors
		
		PathSection() {
			radius = 1.0f;
		
			positionIni = Vector3D(0.0f,0.0f,0.0f);
			normalIni = Vector3D(0.0f,0.0f,1.0f);;
			
			positionEnd = Vector3D(0.0f,0.0f,1.0f);
			normalEnd = Vector3D(0.0f,0.0f,1.0f);;
			
			this->updateOrthogonalVectors();
		}
		
		PathSection(float radius, Vector3D positionIni, Vector3D normalIni, Vector3D positionEnd, Vector3D normalEnd ) {
			this->radius = radius;
			
			this->positionIni = positionIni;
			this->normalIni = normalIni;
			this->positionEnd = positionIni;
			this->normalEnd = normalIni;

			this->updateOrthogonalVectors();
		}
		
		//seters
		void setRadius(float radius);
		
		void setPositionIni( Vector3D newPosition );
		void setNormalIni( Vector3D newOrientation );
		
		void setPositionEnd( Vector3D newPosition );
		void setNormalEnd( Vector3D newOrientation );
		
		//geters
		float getRadius();
		
		Vector3D getPositionIni();
		Vector3D getOrientationIni();
		
		Vector3D getPositionEnd();
		Vector3D getOrientationEnd();
		
		//utils
		void updateOrthogonalVectors();
		void updateOrthogonalVectorsIni();
		void updateOrthogonalVectorsEnd();
		
		Vector3D getPointAtDegree(Vector3D axis, Vector3D orthogonal1, Vector3D orthogonal2, float degree){
			float theta = degree*PI/180.0f;
			GLfloat x = axis.getX() + radius*cos(theta)*orthogonal1.getX() + radius*sin(theta)*orthogonal2.getX();
			GLfloat y = axis.getY() + radius*cos(theta)*orthogonal1.getY() + radius*sin(theta)*orthogonal2.getY();
			GLfloat z = axis.getZ() + radius*cos(theta)*orthogonal1.getZ() + radius*sin(theta)*orthogonal2.getZ();
			return Vector3D(x, y, z);
		}
		
		Vector3D getPointAtDegreeIni(float degree){
			return getPointAtDegree(normalIni,degree);
		}
		
		Vector3D getPointAtDegreeEnd(float degree){
			return getPointAtDegree(normalEnd,degree);
		}
		
		
};
#endif

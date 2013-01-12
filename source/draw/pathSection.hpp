#ifndef PATH_SECTION_H
#define PATH_SECTION_H
class PathSection {
	
	float radius;
	int numberOfSegments;
	
	Vector3D positionIni;
	Vector3D normalIni;
	
	//los vectores End asumen que el origen esta centrado en positionIni
	Vector3D positionEnd;		
	Vector3D normalEnd;
	
	
	vector<Obstacle*> obstacles;
	vector<BlueSphere*> blueSpheres;
	vector<WhiteSphere*> whiteSpheres;
	
	public:
	
		//constructors
		
		PathSection() {
			radius = 1.0f;
			
			numberOfSegments = 1;
		
			positionIni = Vector3D(0.0f,0.0f,0.0f);
			normalIni = Vector3D(0.0f,0.0f,1.0f);
			
			positionEnd = Vector3D(0.0f,0.0f,1.0f);
			normalEnd = Vector3D(0.0f,0.0f,1.0f);
			
			for(int i = 0; i<84; i++){
				if(i%5==0)
					obstacles.push_back(new Obstacle);
				else
					obstacles.push_back(NULL);
					
				if(i%7==0)
					blueSpheres.push_back(new BlueSphere);
				else
					blueSpheres.push_back(NULL);
					
				if(i%6==0)
					whiteSpheres.push_back(new WhiteSphere);
				else
					whiteSpheres.push_back(NULL);
				
			}
			
		}
		
		PathSection(float radius, Vector3D positionIni, Vector3D normalIni, Vector3D positionEnd, Vector3D normalEnd, int numberOfSegments ) {
			this->radius = radius;
			
			this->positionIni = positionIni;
			this->normalIni = normalIni;

			this->positionEnd = positionEnd;
			this->normalEnd = normalEnd;

			this->numberOfSegments = numberOfSegments;

		}
		
		//seters
		void setRadius(float newRadius);
		void setNumberOfSegments(int newNumberOfSegments);
		
		
		void setPositionIni( Vector3D newPosition );
		void setNormalIni( Vector3D newOrientation );
		
		void setPositionEnd( Vector3D newPosition );
		void setNormalEnd( Vector3D newOrientation );
		
		//geters
		float getRadius();
		int getNumberOfSegments();
		
		Vector3D getPositionIni();
		Vector3D getNormalIni();
		
		Vector3D getPositionEnd();
		Vector3D getNormalEnd();
		
		//utils
		bool thereIsObstacle(int i);
		bool thereIsBlueSphere(int i);
		bool thereIsWhiteSphere(int i);
		Obstacle* getObstacle(int i);
		BlueSphere* getBlueSphere(int i);
		WhiteSphere* getWhiteSphere(int i);
		Vector3D getPointAtDegree(Vector3D axis, Vector3D orthogonal1, Vector3D orthogonal2, float degree);
};
#endif

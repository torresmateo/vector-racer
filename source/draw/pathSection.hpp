#ifndef PATH_SECTION_H
#define PATH_SECTION_H

//clase que reprsenta una sección del túnel
class PathSection {
	
    //radio de la sección
	float radius;
    //número de segmentos que componen la sección
	int numberOfSegments;
	
    //posición inicial del centro de la sección
	Vector3D positionIni;
    //normal inicial, perpendicular a un corte transversal al inicio de la sección
    //indica la orientación del corte transversal
	Vector3D normalIni;
	
	//los vectores End asumen que el origen esta centrado en positionIni
    //y son análogos a los vectores Ini
	Vector3D positionEnd;		
	Vector3D normalEnd;
	
    //vector de obstáculos de la sección	
	vector<Obstacle*> obstacles;
    //vector de esferas azules de la sección
	vector<BlueSphere*> blueSpheres;
    //vector de esferas blancas de la sección
	vector<WhiteSphere*> whiteSpheres;
    //vector de esferas fucsias de la sección
	vector<FuchsiaSphere*> fuchsiaSpheres;
    
    //borrar obstáculos y esferas de la sección
	void deleteItems();
    //generar obstáculos y esferas de la sección
	void createItems();
    //generar obstáculos y esferas de la sección ignorando los primeros "segmentsLeftOut" segments
	void createItems( int segmentsLeftOut );
	
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
				obstacles.push_back(NULL);
				blueSpheres.push_back(NULL);
				whiteSpheres.push_back(NULL);
				fuchsiaSpheres.push_back(NULL);
			}
			
			createItems();
		}
		
		PathSection( int segmentsLeftOut ) {
			radius = 1.0f;
			
			numberOfSegments = 1;
		
			positionIni = Vector3D(0.0f,0.0f,0.0f);
			normalIni = Vector3D(0.0f,0.0f,1.0f);
			
			positionEnd = Vector3D(0.0f,0.0f,1.0f);
			normalEnd = Vector3D(0.0f,0.0f,1.0f);
			
			for(int i = 0; i<84; i++){
				obstacles.push_back(NULL);
				blueSpheres.push_back(NULL);
				whiteSpheres.push_back(NULL);
				fuchsiaSpheres.push_back(NULL);
			}
			
			createItems( segmentsLeftOut );
		}
		
		PathSection(float radius, Vector3D positionIni, Vector3D normalIni, Vector3D positionEnd, Vector3D normalEnd, int numberOfSegments ) {
			this->radius = radius;
			
			this->positionIni = positionIni;
			this->normalIni = normalIni;

			this->positionEnd = positionEnd;
			this->normalEnd = normalEnd;

			this->numberOfSegments = numberOfSegments;
			
			for(int i = 0; i<100; i++){
				obstacles.push_back(NULL);
				blueSpheres.push_back(NULL);
				whiteSpheres.push_back(NULL);
				fuchsiaSpheres.push_back(NULL);
			}
			
			createItems();
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
        
        //regenerar los obstáculos y esferas de la sección
		void resetItems();
        //regenerar los obstáculos y esferas de la sección ignorando los primeros "segmentsLeftOut" segmentos
		void resetItems(int segmentsLeftOut);
        //retorna true si hay un obstáculo en el segmento i
		bool thereIsObstacle(int i);
        //retorna true si hay una esfera azúl en el segmento i
		bool thereIsBlueSphere(int i);
        //retorna true si hay una esfera blanca en el segmento i
		bool thereIsWhiteSphere(int i);
        //retorna true si hay una esfera fucsia en el segmento i
		bool thereIsFuchsiaSphere(int i);
        //retorna el obtáculo del segmento i
		Obstacle* getObstacle(int i);
        //retorna la esfera azúl del segmento i
		BlueSphere* getBlueSphere(int i);
        //retorna la esfera blanca del segmento i
		WhiteSphere* getWhiteSphere(int i);
        //retorna la esfera fucsia del segmento i
		FuchsiaSphere* getFuchsiaSphere(int i);
};
#endif

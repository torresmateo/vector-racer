
// enumeracion para el tipo de objeto
enum obstacleType { 
	PYRAMID,
	CUBE,
	CYLINDER
};

// definicion de la class utilizada para los obstaculos
class Obstacle {
	// tipo de objeto
	obstacleType type;
	// posicion lateral del objeto
	float shift;
	// todo objeto tiene un "radio" 
	// (incluye las figuras no circulares, es la longitud horizontal del centro hasta el extremo de la figura)
	float radius;
	// altura de la figura
	float height;
	// utilizada para el cilindro
	GLUquadric *quadric;
	// bandera que indica si el objeto ya se ha activado, con su respectivo efecto
	bool triggered;
	
	public:
		// el constructor elige de forma aleatoria el tipo de objeto,
		// teniendo en cuenta las especificaciones del TP.
		// tambien se elige una posicion lateral aleatoria (shift)
		Obstacle(){
			triggered = false;
			int randomInt = (int)customRand(0,99,0);
			if( randomInt < 60 ){
				type = PYRAMID;
				radius = 0.035f;
				height = 0.12f;
			}else if( randomInt < 60+25 ){
				type = CUBE;
				radius = 0.06f;
				height = radius*2.0;
			}else{
				type = CYLINDER;
				quadric = gluNewQuadric();
				radius = 0.01f;
				height = 0.18f;
				// gluQuadricDrawStyle(quadric, GLU_FILL);
				// gluQuadricOrientation(quadric, GLU_INSIDE);
			}
			shift = customRand(-ROAD_LIMIT+radius, ROAD_LIMIT-radius, 3);
		}
		
		~Obstacle(){
			if( type == CYLINDER )
				gluDeleteQuadric(quadric);
		}
		
		void draw();
		bool isCollision();
		void trigger();
		
		float getShift();
		float getRadius();
		float getHeight();
		
		void setShift( float newShift );
		void setRadius( float newRadius );
		void setHeight( float newHeight );
};










enum obstacleType { 
	PYRAMID,
	CUBE,
	CYLINDER
};

class Obstacle {
	obstacleType type;
	float shift;
	float radius;
	float height;
	GLUquadric *quadric;
	bool triggered;
	
	public:
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









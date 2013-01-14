
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
	public:
		Obstacle(){
			int randomInt = (int)customRand(0,99,0);
			if( randomInt < 60 ){
				type = PYRAMID;
				radius = 0.02f;
				height = 0.08f;
			}else if(randomInt < 60+25){
				type = CUBE;
				radius = 0.04f;
				height = 0.08f;
			}else{
				type = CYLINDER;
				quadric = gluNewQuadric();
				radius = 0.02f;
				height = 0.08f;
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
		
		float getShift();
		float getRadius();
		float getHeight();
		
		void setShift( float newShift );
		void setRadius( float newRadius );
		void setHeight( float newHeight );
};









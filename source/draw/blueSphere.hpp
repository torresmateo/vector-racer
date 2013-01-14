
class BlueSphere {
	float shift;
	float radius;
	
	public:
		BlueSphere(){
			radius = 0.04f;
			shift = customRand(-ROAD_LIMIT+radius, ROAD_LIMIT-radius, 3);
		}
		
		void draw();
		bool isCollision();
		
		float getShift();
		float getRadius();
		
		void setShift( float newShift );
		void setRadius( float newRadius );
};









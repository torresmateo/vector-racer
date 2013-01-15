
class WhiteSphere {
	float shift;
	float radius;
	
	public:
		WhiteSphere(){
			radius = 0.02f;
			shift = customRand(-ROAD_LIMIT+radius, ROAD_LIMIT-radius, 3);
		}
		
		WhiteSphere(float otherShift, float otherRadius){
			radius = 0.02f;
			shift = customRand(-ROAD_LIMIT+radius, ROAD_LIMIT-radius, 3);
			while( fabs(shift-otherShift) < radius+otherRadius ){
				shift = customRand(-ROAD_LIMIT+radius, ROAD_LIMIT-radius, 3);
			}
		}
		
		void draw();
		bool isCollision();
		
		float getShift();
		float getRadius();
		
		void setShift( float newShift );
		void setRadius( float newRadius );
};









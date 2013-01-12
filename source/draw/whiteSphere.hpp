
class WhiteSphere {
	float shift;
	float radius;
	
	public:
		WhiteSphere(){
			radius = 0.04f;
			shift = customRand(-ROAD_LIMIT+radius, ROAD_LIMIT-radius, 3);
		}
		
		void draw();

};









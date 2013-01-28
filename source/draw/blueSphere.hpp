//clase de la Esfera, que cuenta con el efecto de
//reducir la velocidad en un factor de 1.1 
//como respuesta a la colisión
class BlueSphere {
    //offset horizontal
	float shift;
    //radio de la esfera
	float radius;
    //bandera de uso del evento de colisión
	bool triggered;
	
	public:
        //constructores
		BlueSphere(){
			triggered = false;
			radius = 0.035f;
			shift = customRand(-ROAD_LIMIT+radius, ROAD_LIMIT-radius, 3);
		}
		
		BlueSphere(float otherShift, float otherRadius){
			triggered = false;
			radius = 0.035f;
			shift = customRand(-ROAD_LIMIT+radius, ROAD_LIMIT-radius, 3);
			while( fabs(shift-otherShift) < radius+otherRadius ){
				shift = customRand(-ROAD_LIMIT+radius, ROAD_LIMIT-radius, 3);
			}
		}
		
        //función de dibujado
		void draw();
        //detección de colisión
		bool isCollision();
        //evento de colisión
		void trigger();
		
        //getters
		float getShift();
		float getRadius();
		
        //setters
		void setShift( float newShift );
		void setRadius( float newRadius );
};









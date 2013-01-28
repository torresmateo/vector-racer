
//clase que representa a la esfera blanca, con el efecto 
//de agregar una vida a la nave en caso de que no cuenta con
//el máximo de vidas
class WhiteSphere {
    //offset horizontal
	float shift;
    //radio de la esfera
	float radius;
    //bandera de uso del evento de colisión
	bool triggered;
	
	public:
        //constructores
		WhiteSphere(){
			triggered = false;
			radius = 0.02f;
			shift = customRand(-ROAD_LIMIT+radius, ROAD_LIMIT-radius, 3);
		}
		
		WhiteSphere(float otherShift, float otherRadius){
			triggered = false;
			radius = 0.02f;
			shift = customRand(-ROAD_LIMIT+radius, ROAD_LIMIT-radius, 3);
			while( fabs(shift-otherShift) < radius+otherRadius ){
				shift = customRand(-ROAD_LIMIT+radius, ROAD_LIMIT-radius, 3);
			}
		}
		
        //función de dibujado
		void draw();
        //detección de colisión
		bool isCollision();
        //handler del evento de colisión con la esfera
		void trigger();
		
        //getters
		float getShift();
		float getRadius();
		
        //setters
		void setShift( float newShift );
		void setRadius( float newRadius );
};









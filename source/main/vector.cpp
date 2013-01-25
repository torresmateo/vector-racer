extern string gDEBUG;
/************************************************************
	vector tridimensional
*************************************************************/
class Vector3D {
	double x,y,z; // componentes
	
	public:
	
		// =====================
		//		constructors
		// =====================	
		
		Vector3D() {
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}
		
		Vector3D( double newX, double newY, double newZ ) {
			this->x = newX;
			this->y = newY;
			this->z = newZ;
		}
		
		// =====================
		//		seters
		// =====================
		
		void setX( double newX ) { this->x = newX; }
		void setY( double newY ) { this->y = newY; }
		void setZ( double newZ ) { this->z = newZ; }

		void setXYZ( double newX, double newY, double newZ ) {
			this->x = newX;
			this->y = newY;
			this->z = newZ;
		}
		
		void rotateXZ( double deltaAngle ) {
			double mag = this->getMagXZ();
			double angle = this->getAngleXZ();
			angle += deltaAngle;
			this->x = mag*cos( angle );
			this->z = mag*sin( angle );
		}
		
		void rotateYZ( double deltaAngle ) {
			double mag = this->getMagYZ();
			double angle = this->getAngleYZ();
			angle += deltaAngle;
			this->y = mag*cos( angle );
			this->z = mag*sin( angle );
		}
		
		
		void setAngleXZ( double angle ) {
			double mag = this->getMagXZ();
			this->x = mag*cos( angle );
			this->z = mag*sin( angle );
		}
		
		void setAngleYZ( double angle ) {
			double mag = this->getMagYZ();
			this->y = mag*cos( angle );
			this->z = mag*sin( angle );
		}
		
		void rotateYH( double angle ) {
			double saveAngleXZ = this->getAngleXZ();
			this->setAngleXZ( HALF_PI );
			this->rotateYZ( angle );
			this->setAngleXZ( saveAngleXZ );
		}
		
		// =====================
		//		geters
		// =====================	
		
		double getX() { return x; }
		double getY() { return y; }
		double getZ() { return z; }
		
		double getMag() { // magnitud
			return sqrt( pow(x,2) + pow(y,2) + pow(z,2) );
		}
		
		double getMagXZ() { // magnitud
			return sqrt( pow(x,2) + pow(z,2) );
		}
		
		double getMagYZ() { // magnitud
			return sqrt( pow(y,2) + pow(z,2) );
		}
		
		double getAngleXZ() {
			return atan2(z,x);
		}
		
		double getAngleYZ() {
			return atan2(z,y);
		}
		
		double getAngleYH() {
			Vector3D tempVec(*this);
			tempVec.setAngleXZ(HALF_PI);
			return tempVec.getAngleYZ();
		}
		
		string toString(){
			return "[" + doubleToStr(x) + "] [" + doubleToStr(y) + "] [" + doubleToStr(z) + "]";  
		}
		
		// =====================
		//		operadores
		// =====================	
		
		Vector3D operator +( Vector3D otherVec ) {
			otherVec.x += this->x;
			otherVec.y += this->y;
			otherVec.z += this->z;
			return otherVec;
		}
		
		Vector3D operator -( Vector3D otherVec ) {
			otherVec.x =  this->x - otherVec.x;
			otherVec.y =  this->y - otherVec.y;
			otherVec.z =  this->z - otherVec.z;
			return otherVec;
		}
		
		Vector3D operator *( double c ) { // producto con escalar
			Vector3D tempVec( this->x*c, this->y*c, this->z*c);
			return tempVec;
		}
		
		Vector3D operator +=( Vector3D otherVec ) {
			this->x += otherVec.x;
			this->y += otherVec.y;
			this->z += otherVec.z;
			return *this;
		}
		
		Vector3D operator -=( Vector3D otherVec ) {
			this->x -= otherVec.x;
			this->y -= otherVec.y;
			this->z -= otherVec.z;
			return *this;
		}
		
		Vector3D getNormalizedVector(){
			float norm = sqrt(pow(this->x,2) + pow(this->y,2) + pow(this->z,2));
			Vector3D resultVector(this->x/norm,this->y/norm,this->z/norm);
			return resultVector;
		}
		
		Vector3D setNormalized(){
			*this = this->getNormalizedVector();
			return *this;
		}
		
		Vector3D getUnitaryPerpendicularVector(){
			float x0 = 0, y0 = 0, z0 = 0;			
			x0 = 0;
			y0 = this->z;
			z0 = -(this->y);
		
			Vector3D resultVector(x0,y0,z0);
			return resultVector.getNormalizedVector();
		}
		
		static Vector3D crossMultiply(Vector3D u, Vector3D v){
			float a = u.getY()*v.getZ() - u.getZ()*v.getY();
			float b = u.getZ()*v.getX() - u.getX()*v.getZ();
			float c = u.getX()*v.getY() - u.getY()*v.getX();
			Vector3D resultVector(a,b,c);
			return resultVector;
		}
		
		
		
};



/************************************************************
	vector bidimensional
*************************************************************/
class Vector2D {
	double x,y; // componentes
	
	public:
	
		// =====================
		//		constructors
		// =====================	
		
		Vector2D() {
			this->x = 0;
			this->y = 0;
		}
		
		Vector2D( double newX, double newY ) {
			this->x = newX;
			this->y = newY;
		}
		
		// =====================
		//		seters
		// =====================	
		
		void setX( double newX ) { this->x = newX; }
		void setY( double newY ) { this->y = newY; }
		
		void setW( double newW ) { this->x = newW; }
		void setH( double newH ) { this->y = newH; }
		
		void setXY( double newX, double newY ) {
			this->x = newX;
			this->y = newY;
		}
		
		void setWH( double newX, double newY ) {
			this->x = newX;
			this->y = newY;
		}
		
		// =====================
		//		geters
		// =====================	
		
		double getX() { return x; }
		double getY() { return y; }
		
		double getW() { return x; }
		double getH() { return y; }
		
		double getMag() { // magnitud
			return sqrt( pow(x,2) + pow(y,2) );
		}
		
		double getAngle() {
			return atan2( y, x );
		}
		
		string toString(){
			return "[" + doubleToStr(x) + "] [" + doubleToStr(y) + "]";  
		}
		
		// double getAngleWith( Vector2D otherVec ) {
			// return atan2( otherVec.y - this->y, otherVec.x - this->x );
		// }
		
		// double squaredDistanceTo( Vector2D otherVec ) {
			// return pow(otherVec.y - this->y, 2) + pow(otherVec.x - this->x, 2);
		// } 
		
		// double distanceTo( Vector2D otherVec ) {
			// return sqrt( pow(otherVec.y - this->y, 2) + pow(otherVec.x - this->x, 2) );
		// } 	
		
		// =====================
		//		operadores
		// =====================	
		
		Vector2D operator +( Vector2D otherVec ) {
			otherVec.x += this->x;
			otherVec.y += this->y;
			return otherVec;
		}
		
		Vector2D operator -( Vector2D otherVec ) {
			otherVec.x =  this->x - otherVec.x;
			otherVec.y =  this->y - otherVec.y;
			return otherVec;
		}
		
		
		Vector2D operator *( double c ) { // producto con escalar
			Vector2D tempVec( x*c, y*c);
			return tempVec;
		}
		
		Vector2D operator +=( Vector2D otherVec ) {
			this->x += otherVec.x;
			this->y += otherVec.y;
			return *this;
		}
};




























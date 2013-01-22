#ifndef MATRIX_3_H
#define MATRIX_3_H

class Matrix3{
	Vector3D row1;
	Vector3D row2;
	Vector3D row3;
	
	public:
		//constructors
		//por defecto es la identidad
		Matrix3(){
			row1 = Vector3D(1.0f,0.0f,0.0f);
			row2 = Vector3D(0.0f,1.0f,0.0f);
			row3 = Vector3D(0.0f,0.0f,1.0f);
		}
	
		Matrix3(Vector3D row1, Vector3D row2, Vector3D row3){
			this->row1 = row1;
			this->row2 = row2;
			this->row3 = row3;
		}
	
		Matrix3(	float x1, float y1, float z1,
				float x2, float y2, float z2,
				float x3, float y3, float z3){
			row1 = Vector3D(x1, y1, z1);
			row2 = Vector3D(x2, y2, z2);
			row3 = Vector3D(x3, y3, z3);
		}
	
		//setters
		void setRow1( Vector3D newRow1 );
		void setRow2( Vector3D newRow2 );
		void setRow3( Vector3D newRow3 );
		
		//getters
		Vector3D getRow1();
		Vector3D getRow2();
		Vector3D getRow3();
		
		//operadores
	
		Matrix3 operator +=( Matrix3 otherMatrix ){
			row1 += otherMatrix.getRow1();
			row2 += otherMatrix.getRow2();
			row3 += otherMatrix.getRow3();
			return *this;
		}
		Matrix3 operator -=( Matrix3 otherMatrix ){
			row1 -= otherMatrix.getRow1();
			row2 -= otherMatrix.getRow2();
			row3 -= otherMatrix.getRow3();
			return *this;
		}
		Vector3D operator *=( Vector3D vertex ){
			float x,y,z;
			x = this->getRow1().getX()*vertex.getX() + this->getRow1().getY()*vertex.getY() + this->getRow1().getZ()*vertex.getZ();
			y = this->getRow2().getX()*vertex.getX() + this->getRow2().getY()*vertex.getY() + this->getRow2().getZ()*vertex.getZ();
			z = this->getRow3().getX()*vertex.getX() + this->getRow3().getY()*vertex.getY() + this->getRow3().getZ()*vertex.getZ();
			return Vector3D(x,y,z);
		}
		Matrix3 operator *=( double escalar ){
			row1 = row1*escalar;
			row2 = row2*escalar;
			row3 = row3*escalar;
			return *this;
		}
		
		//utils
		static Matrix3 scalarMultiply(Matrix3 matrix, double scalar){
			matrix.setRow1(matrix.getRow1()*scalar);		
			matrix.setRow2(matrix.getRow2()*scalar);
			matrix.setRow3(matrix.getRow3()*scalar);
	
			return matrix;
		}		
};


#endif

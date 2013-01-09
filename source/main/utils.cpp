

/************************************************************
	matrices de transformación
*************************************************************/

Vector3D rotateVertex(Vector3D vertex, Vector3D axis, float degrees){
	float rad = degrees * (PI/180);	
	axis.setNormalized();
	
	float x = axis.getX();	
	float y = axis.getY();
	float z = axis.getZ();

	Matrix3 identity(1.0f,0.0f,0.0f,
					 0.0f,1.0f,0.0f,
					 0.0f,0.0f,1.0f);
	Matrix3 aaT = Matrix3(	x*x, x*y, x*z,
							x*y, y*y, y*z,
							x*z, y*z, z*z);

	Matrix3 aStar = Matrix3(	0.0f, -z		,  y		,
							z	, 0.0f	, -x		,
							-y	, x		, 0.0f	);
	Matrix3 aux1 = Matrix3::scalarMultiply(identity, cos(rad));
	//printf("(%f),%f,%f,%f\n\n",1-cos(rad),GET_TRIPLET(aux1.getRow1()));
	Matrix3 aux2 = Matrix3::scalarMultiply(aaT, (1-cos(rad)));
	Matrix3 aux3 = Matrix3::scalarMultiply(aStar, sin(rad));
	
	aux1+=aux2;
	aux1+=aux3;
	
	return aux1*=vertex;
	
}

Vector3D translateVertex(Vector3D vertex, Vector3D translationPoint){
	return vertex+=translationPoint;
}

/************************************************************
	calculo de frame rate
*************************************************************/
void calculateFPS() {
	gFRAME++;
	gTIME=glutGet(GLUT_ELAPSED_TIME);
	if (gTIME - gTIMEBASE > 1000) {
		gFPS = gFRAME*1000.0/(gTIME-gTIMEBASE);
		gTIMEBASE = gTIME;
		gFRAME = 0;
	}
}

void updateCameraLookAt(){
	// actualiza el punto a mirar 
	gCAM_LOOK_AT = gCAM_POS+gCAM_DIR;
	// posiciona vista
	gluLookAt(
		GET_TRIPLET(gCAM_POS),
		GET_TRIPLET(gCAM_LOOK_AT),
		0.0f, 1.0f,  0.0f
	);
}

void updateCameraLookAt( Vector3D position, Vector3D direction ){
	Vector3D camLookAt = position + direction;
	// posiciona vista
	gluLookAt(
		GET_TRIPLET(position),
		GET_TRIPLET(camLookAt),
		0.0f, 1.0f,  0.0f
	);
}

string intToStr(int num) {
   stringstream ss;
   ss << num;
   return ss.str();
}

string doubleToStr(double num) {
   stringstream ss;
   ss << num;
   return ss.str();
}


void loadPath(){

	Vector3D aux1(0,0,0);
	Vector3D aux2(0,0,1);
	Vector3D aux3(0,0,3);
	Vector3D aux4(0,-0.1f,1);
	
	
	
	
	Vector3D aux5(0,0,0);
	Vector3D aux6(0,0,1);
	Vector3D aux7(0,0,5);
	Vector3D aux8(0.1f,0,1.1f);
	
	PathSection seccion(	1.0, 
		aux1, aux2,
		aux3, aux4,
		1
	);
	PathSection seccion2(	1.0, 
		aux5, aux6,
		aux7, aux8,
		1
	);

	gTUNNEL_PATH.pushSection(seccion);
	gTUNNEL_PATH.pushSection(seccion);
	gTUNNEL_PATH.pushSection(seccion);
	gTUNNEL_PATH.pushSection(seccion);
	gTUNNEL_PATH.pushSection(seccion2);
}




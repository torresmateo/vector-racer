

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


/************************************************************
	funciones que determinan la forma de la carretera
*************************************************************/

PathSection torusSection(float innerRadius, float outerRadius, unsigned int rings, float sectionAngleDeg, float orientationAngleDeg){
	//innerRadius: el radio de cada segmento
	//outerRadius: el radio del torus
	//rings: cuantos segmentos tiene esta sección
	//sectionAngleDeg que tantos grados del toro abarca
	//orientationAngleDeg hacia donde se curva el toro
	
	float segmentAngleDeg = sectionAngleDeg/rings; //ángulo abarcado por cada segmento
	float x = outerRadius * cos(orientationAngleDeg * (PI/180));
	float y = outerRadius * sin(orientationAngleDeg * (PI/180));
	Vector3D radiusVector(-x,-y,0);//negativo para poder usar el origen como punto de rotación
	Vector3D rotateAxis(0,0,1);
	rotateAxis = Vector3D::crossMultiply(rotateAxis,radiusVector);
	Vector3D rotatedRadius = rotateVertex(radiusVector,rotateAxis,segmentAngleDeg);
	Vector3D tanVector = rotateVertex(Vector3D(0,0,1),rotateAxis,segmentAngleDeg);
	PathSection torus;
	torus.setRadius(innerRadius);
	torus.setPositionEnd(radiusVector - rotatedRadius);
	torus.setNormalEnd(tanVector);
	torus.setNumberOfSegments(rings);
	return torus;

}


void loadPath(){

	Vector3D aux1(0,0,0);
	Vector3D aux2(0,0,1);
	Vector3D aux3(0,0,0.5f);
	Vector3D aux4(0,-0.1f,1);
	
	
	
	
	Vector3D aux5(0,0,0);
	Vector3D aux6(0,0,1);
	Vector3D aux7(0,0,0.5f);
	Vector3D aux8(0.1f,0.1f,1);
	
	int rings = 50;
	float sectionAngle = 45.0f;
	PathSection seccion (torusSection(0.5f, 10.0f,rings, sectionAngle, 0.0f));
	PathSection seccion2(torusSection(0.5f, 10.0f,rings, sectionAngle, 180.0f));
	PathSection seccion3(torusSection(0.5f, 10.0f,rings, sectionAngle, 45.0f));
	PathSection seccion4(torusSection(0.5f, 10.0f,rings, sectionAngle, -45.0f));
	

	gTUNNEL_PATH.pushSection(seccion);
	gTUNNEL_PATH.pushSection(seccion2);
	gTUNNEL_PATH.pushSection(seccion3);
	gTUNNEL_PATH.pushSection(seccion4);
}




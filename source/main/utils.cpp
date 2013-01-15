

/************************************************************
	matrices de transformación
*************************************************************/

Vector3D rotateVertex(Vector3D vertex, Vector3D axis, float degrees){
	float rad = degrees * (PI/180);	
	
	if(axis.getX()==0 and axis.getY()==0 and axis.getZ()==0 )
		return vertex;
		
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

	Matrix3 aStar = Matrix3(0.0f, -z 	,  y		,
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

	int rings = 84;
	float sectionAngle = 60.160568f;
	float outerRadius = 40.0f;
	
	int ringsDownCase = 84;
	float sectionAngleDownCase = 24.064227;
	float outerRadiusDownCase = 100.0f;
	
	float torusOrientation = 0.0f;
	
	// PathSection seccion(torusSection(0.5f, 40.0f,rings, sectionAngle, 270.0f));
	// PathSection seccion2(torusSection(0.5f, 100.0f,ringsDownCase, sectionAngleDownCase, 90.0f));
	// PathSection seccion3(torusSection(0.5f, 40.0f,rings, sectionAngle, 270.0f));
	// PathSection seccion4(torusSection(0.5f, 80.0f,rings, sectionAngle, 90.0f));
	
	PathSection auxPath(15);
	auxPath.setRadius(0.5f);
	Vector3D auxPositionEnd(0.0f,0.0f,0.5f);
	auxPath.setPositionEnd(auxPositionEnd);
	auxPath.setNumberOfSegments(84);
	
	gCURVES[0] = auxPath;
	
	for(int i = 1; i<9; i++){
		if( 0 < torusOrientation and torusOrientation < 180 )
			gCURVES[i] = torusSection(0.5f, outerRadiusDownCase, ringsDownCase, sectionAngleDownCase, torusOrientation);
		else
			gCURVES[i] = torusSection(0.5f, outerRadius, rings, sectionAngle, torusOrientation);
		torusOrientation += 45;
	}
	int index = 0;
	gPREV_INDEX[0] = index;
	gTUNNEL_PATH.pushSection(gCURVES[index]);
	
	index = rand()%8 + 1;
	gPREV_INDEX[1] = index;
	gTUNNEL_PATH.pushSection(gCURVES[index]);
	
	index = rand()%8 + 1;
	while( index == gPREV_INDEX[1] ){
		index = rand()%8 + 1;
	}
	gPREV_INDEX[2] = index;
	gTUNNEL_PATH.pushSection(gCURVES[index]);
	
	
}



float customRand( float limitDown, float limitUp, int decimal) {
	float e10decimal = pow(10,decimal);
	int intLimitDown = limitDown * e10decimal;
	int intLimitUp = limitUp * e10decimal;
	return (rand()%(intLimitUp-intLimitDown+1) + intLimitDown)/e10decimal;
}














































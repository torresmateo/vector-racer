

/************************************************************
	matrices de transformación
*************************************************************/


//rotar el vector "vertex" alrededor del eje "axis" por "degrees" grados 
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
	Matrix3 aux2 = Matrix3::scalarMultiply(aaT, (1-cos(rad)));
	Matrix3 aux3 = Matrix3::scalarMultiply(aStar, sin(rad));
	
	aux1+=aux2;
	aux1+=aux3;
	
	return aux1*=vertex;
}

//translada el vector "vertex" hasta "translationPoint"
Vector3D translateVertex(Vector3D vertex, Vector3D translationPoint){
	return vertex+=translationPoint;
}

/************************************************************
	calculo de frame rate
*************************************************************/
//calcula los frames por segundo
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

//conversor de entero a string
string intToStr(int num) {
   stringstream ss;
   ss << num;
   return ss.str();
}

//conversor de double a string
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

//carga el Path predefinido
void loadPath(){
    //cantidad de segmentos
	int rings = 84;
    //angulo que abarca la curva 
	float sectionAngle = 60.160568f;
    //radio de la curva
	float outerRadius = 40.0f;
	
    //para el caso particular de la curva hacia abajo
	int ringsDownCase = 84;
	float sectionAngleDownCase = 24.064227;
	float outerRadiusDownCase = 100.0f;
	
    //orientacion inicial de la curva
	float torusOrientation = 0.0f;
	
    //secccion auxiliar
	PathSection auxPath(15);
    //configuramos el radio del tunel
	auxPath.setRadius(0.5f);
    //definimos la posicion del segmento logrando un tunel sin curva
	Vector3D auxPositionEnd(0.0f,0.0f,0.5f);
	auxPath.setPositionEnd(auxPositionEnd);
    //definimos la cantidad de segmentos para igualar a los del path normal
	auxPath.setNumberOfSegments(84);
	
    //agregamos la sección auxiliar a nuestro vector de curvas predefinidas
	gCURVES[0] = auxPath;
	
    //creamos 8 curvas cada 45 grados y agregamos al vector de curvas predefinidas
	for(int i = 1; i<9; i++){
		if( 0 < torusOrientation and torusOrientation < 180 )
			gCURVES[i] = torusSection(0.5f, outerRadiusDownCase, ringsDownCase, sectionAngleDownCase, torusOrientation);
		else
			gCURVES[i] = torusSection(0.5f, outerRadius, rings, sectionAngle, torusOrientation);
		torusOrientation += 45;
	}
	
    //iniciamos con tres segmentos rectos
	gTUNNEL_PATH.pushSection(gCURVES[0]);
	gTUNNEL_PATH.pushSection(gCURVES[0]);
	gTUNNEL_PATH.pushSection(gCURVES[0]);
	
}

//mejora el la funcion de random 
float customRand( float limitDown, float limitUp, int decimal) {
	float e10decimal = pow(10,decimal);
	int intLimitDown = limitDown * e10decimal;
	int intLimitUp = limitUp * e10decimal;
	return (rand()%(intLimitUp-intLimitDown+1) + intLimitDown)/e10decimal;
}

//manejador de colisiones
void collisionHandler(){
	//indice del segmento actual
	int CurentIndex = gTUNNEL_PATH.getCurrentSegmentsIndex()+2;
	//seccion actual
	PathSection currentSection(gTUNNEL_PATH.getCurrentSection());
	
	if(CurentIndex >= currentSection.getNumberOfSegments()){
		CurentIndex = CurentIndex - (currentSection.getNumberOfSegments());
		currentSection = gTUNNEL_PATH.getNextSection();
	}
	
	if(currentSection.thereIsWhiteSphere(CurentIndex) and currentSection.getWhiteSphere(CurentIndex)->isCollision()){
		currentSection.getWhiteSphere(CurentIndex)->trigger();
	}
	
	if(currentSection.thereIsBlueSphere(CurentIndex) and currentSection.getBlueSphere(CurentIndex)->isCollision()){
		currentSection.getBlueSphere(CurentIndex)->trigger();
	}
	
	if(currentSection.thereIsObstacle(CurentIndex) and currentSection.getObstacle(CurentIndex)->isCollision()){
		currentSection.getObstacle(CurentIndex)->trigger();
		if( !gCAR_HEALTH and !gDEBUG_MODE )
			gIN_GAME_STATE = GAME_OVER_INIT;
	}
}

//resetea el valor por defecto de los materiales de OpenGL
void resetMaterials(){
	float diffuse[]={0.2, 0.2, 0.2, 1.0};
	float ambient[]={0.8, 0.8, 0.8, 1.0};
	float specular[]={0.0, 0.0, 0.0, 1.0};

	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
	//glMaterialf(GL_FRONT,GL_SHININESS,0);
}


//inicialización del juego
void gameInitialization(){
	int index = 0;
	
	//la primera parte del camino viene sin obstaculos
	gTUNNEL_PATH.nextSection();	
	gPREV_INDEX[0] = index;
	gCURVES[index].resetItems(15);
	gTUNNEL_PATH.pushSection(gCURVES[index]);
	
	gTUNNEL_PATH.nextSection();	
	index = rand()%8 + 1;
	gPREV_INDEX[1] = index;
	gCURVES[index].resetItems();
	gTUNNEL_PATH.pushSection(gCURVES[index]);
	
	gTUNNEL_PATH.nextSection();	
	index = rand()%8 + 1;
	while( index == gPREV_INDEX[1] )
		index = rand()%8 + 1;
	gPREV_INDEX[2] = index;
	gCURVES[index].resetItems();
	gTUNNEL_PATH.pushSection(gCURVES[index]);
	
	//inicialización de la cámara
	gCAM_POS.setXYZ(0.0f,0.0f,0.0f);
	gCAM_DIR.setXYZ(0.0f,0.0f,1.0f);
	//inicialización de los puntajes, posicion y velocidad del juego
	gSCORE = 0;
	gCAR_POS.setX(0);
	gCAR_HEALTH = 3;
	gCAR_SPEED = 0.2;
	gCAR_TILT = 0;
	gCAR_LAST_X = 0;
	gSCORE_STATE = NONE;
	gPLAYER_NAME = "";
	gCONGRATS_DONE = false;
	
	//pausar la musica del menu
	gMENU_MUSIC->setIsPaused();
	//reproducir la musica del juego
	gINGAME_MUSIC->setPlayPosition(0);
	gINGAME_MUSIC->setIsPaused(false);
	//iniciar la suma de puntos
	glutTimerFunc(100,scorePP,100);
}










































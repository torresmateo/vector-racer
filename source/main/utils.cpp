




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










/************************************************************
	funcion para imprimir datos internos relevantes del programa
*************************************************************/
void printVariables(){
	string stringToPrint;
	int shift = 15;
	
	stringToPrint = "Frame Rate: " + intToStr((int)gFPS) + " fps";
	renderBitmapStringProjection( 
		15, gSCREEN.getH()-shift, 0,
		stringToPrint.c_str()
	);
	shift += 25;
	
	stringToPrint = "gCAM_POS: " + gCAM_POS.toString();
	renderBitmapStringProjection( 
		15, gSCREEN.getH()-shift, 0,
		stringToPrint.c_str()
	);
	shift += 25;
	
	stringToPrint = "gCAM_DIR: " + gCAM_DIR.toString();
	renderBitmapStringProjection( 
		15, gSCREEN.getH()-shift, 0,
		stringToPrint.c_str()
	);
	shift += 25;
	
	stringToPrint = "gMOUSE: " + gMOUSE.toString();
	renderBitmapStringProjection( 
		15, gSCREEN.getH()-shift, 0,
		stringToPrint.c_str()
	);
	shift += 25;
	
	stringToPrint = "gDEBUG: " + gDEBUG;
	renderBitmapStringProjection( 
		15, gSCREEN.getH()-shift, 0,
		stringToPrint.c_str()
	);
}


/************************************************************
	funcion principal de renderizado
*************************************************************/
void display(void) {
	
	// Maneja input
	processInput();
	
	// Calculo del frame rate
	calculateFPS();
	
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();
	
	// Set the camera
	updateCameraLookAt();
	
	// pinta el escenario
	drawScene();
	
	
	//	==============================
	//		impresion en pantalla
	//	==============================
	
	// preparacion para impresion en pantalla
	setOrthographicProjection();
		glPushMatrix();
		glLoadIdentity();
		glColor3f(GREEN);
		
		// imprime datos relevantes
		printVariables();
		
		// fin de impresion en pantalla
		glPopMatrix();
	restorePerspectiveProjection();
	
	// Cambio de buffer
	glutSwapBuffers();
}


/************************************************************
	controlador de redimension de la ventana
*************************************************************/
void changeSize(int newWidth, int newHigh) {

	gSCREEN.setW(newWidth);
	gSCREEN.setH(newHigh);
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (gSCREEN.getH() == 0)
		gSCREEN.setH(0);
	
	float ratio =  gSCREEN.getW() / gSCREEN.getH();

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, gSCREEN.getW(), gSCREEN.getH());

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

















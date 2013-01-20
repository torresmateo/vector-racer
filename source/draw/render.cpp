
void displayMainMenu() {
	stringstream ss;
	
	// preparacion para impresion en pantalla
	setOrthographicProjection();
		glPushMatrix();
		glLoadIdentity();
		glColor3f(GREEN);
		
		
		ss << "Play!! ";
		ss << "[SPACE]";
		renderBitmapStringProjection( 
			gSCREEN.getW()/2.0, gSCREEN.getH()/2.0, 0,
			ss.str().c_str()
		);

		ss.str("");
		ss << "[ESC] exit";
		renderBitmapStringProjection( 
			20, 20, 0,
			ss.str().c_str()
		);
		
		printVariables();
		// fin de impresion en pantalla
		glPopMatrix();
	restorePerspectiveProjection();
}

void diplayInstructions(){
	stringstream ss;
	
	// preparacion para impresion en pantalla
	setOrthographicProjection();
		glPushMatrix();
		glLoadIdentity();
		glColor3f(GREEN);
		
		
		ss << "Instrucciones";
		renderBitmapStringProjection( 
			gSCREEN.getW()/2.0, gSCREEN.getH()/2.0, 0,
			ss.str().c_str()
		);
		
		ss.str("");
		ss << "[SPACE] Start when ready";
		renderBitmapStringProjection( 
			gSCREEN.getW()*0.7, gSCREEN.getH()*0.7, 0,
			ss.str().c_str()
		);
		
		ss.str("");
		ss << "[ESC] Back to main menu";
		renderBitmapStringProjection( 
			gSCREEN.getW()*0.7, gSCREEN.getH()*0.7-25, 0,
			ss.str().c_str()
		);
		
		printVariables();
		// fin de impresion en pantalla
		glPopMatrix();
	restorePerspectiveProjection();
}

void displayGameOverScreen(){
	
	// Set the camera
	updateCameraLookAt();
	
	// pinta el escenario
	drawScene();
			
	stringstream ss;
	
	// preparacion para impresion en pantalla
	setOrthographicProjection();
		glPushMatrix();
		glLoadIdentity();
		glColor3f(GREEN);
		
		ss << "GAME OVER";
		renderBitmapStringProjection( 
			gSCREEN.getW()/2.0, gSCREEN.getH()/2.0, 0,
			ss.str().c_str()
		);
		
		ss.str("");
		ss << "[SPACE] Back to main menu";
		renderBitmapStringProjection( 
			20, 20, 0,
			ss.str().c_str()
		);
		
		ss.str("");
		ss << "[ESC] Exit";
		renderBitmapStringProjection( 
			20, 40, 0,
			ss.str().c_str()
		);
		
		printVariables();
		// fin de impresion en pantalla
		glPopMatrix();
	restorePerspectiveProjection();
}

void playing(){
	// Set the camera
	updateCameraLookAt();
	
	// pinta el escenario
	drawScene();
	
	// drawCarCollisionArea();
	drawPositionedCar();
	
	//	==============================
	//		impresion en pantalla
	//	==============================
	
	// preparacion para impresion en pantalla
	setOrthographicProjection();
		glPushMatrix();
		glLoadIdentity();
		glColor3f(GREEN);
		
		// imprime datos del juego
		printGameData();
		
		// imprime datos relevantes
		printVariables();
		
		// fin de impresion en pantalla
		glPopMatrix();
	restorePerspectiveProjection();
	
	collisionHandler();
}

void displayInGame() {
	
	switch( gIN_GAME_STATE ){	
		
		case INSTRUCTIONS:{
			diplayInstructions();
		} break;
		
		case PLAYING:{
			playing();
		} break;
		
		case GAME_OVER_INIT:{
			displayGameOverScreen();
			gIN_GAME_STATE = GAME_OVER;
		} break;
		
		case GAME_OVER:{
			displayGameOverScreen();
		} break;
	}
	
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
	
	switch( gGENERAL_STATE ){
		case MAIN_MENU:{
			displayMainMenu();
		} break;
		
		case GAME_INIT:{
			gameInitialization();
			displayInGame();
			gGENERAL_STATE = IN_GAME;
			gIN_GAME_STATE = INSTRUCTIONS;
		} break;
		
		case IN_GAME:{
			displayInGame();
		} break;
		
		case EXIT:{
			exit(0);
		} break;
	}
	
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
	gluPerspective(45.0f, ratio, 0.01f, 67.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

















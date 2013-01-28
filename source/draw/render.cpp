
/************************************************************
	Funcion para dibujado del menu principal
*************************************************************/
void displayMainMenu() {
	stringstream ss;
	
	// se imprime el top 10
	gRANKING.draw();
	
	// dibujado de la imagen de fondo del main menu
	// (imagen centrada en la pantalla)
	setOrthographicProjection();
		glPushMatrix();{
			glLoadIdentity();
			glColor3f(BLUE);
			
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,gMAIN_MENU_BG);
				glBegin(GL_QUADS);{
				
					glTexCoord2f(0,0);
					glVertex3f( -BG_W/2,  BG_H/2, 0 );
					
					glTexCoord2f(0,1);
					glVertex3f( -BG_W/2, -BG_H/2, 0 );
					
					glTexCoord2f(1,1);
					glVertex3f(  BG_W/2, -BG_H/2, 0 );
					
					glTexCoord2f(1,0);
					glVertex3f(  BG_W/2,  BG_H/2, 0 );
					
				}glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
		}glPopMatrix();
	restorePerspectiveProjection();
}

/************************************************************
	Muestra la pantalla de instrucciones
*************************************************************/
void diplayInstructions(){
	stringstream ss;
	
	// preparacion para impresion en pantalla
	setOrthographicProjection();
		glPushMatrix();
		glLoadIdentity();
		// glColor3f(GREEN);
		
		// fin de impresion en pantalla
		glPopMatrix();
		
		// dibujado de la imgen de fondo para el menu de instrucciones
		glPushMatrix();{
			glLoadIdentity();
			glColor3f(BLUE);
			glTranslatef(0.0f,0.0f,-0.9f);
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,gINSTRUCTIONS_BG);
				glBegin(GL_QUADS);{
				
					glTexCoord2f(0,0);
					glVertex3f( -BG_W/2,  BG_H/2, 0 );
					
					glTexCoord2f(0,1);
					glVertex3f( -BG_W/2, -BG_H/2, 0 );
					
					glTexCoord2f(1,1);
					glVertex3f(  BG_W/2, -BG_H/2, 0 );
					
					glTexCoord2f(1,0);
					glVertex3f(  BG_W/2,  BG_H/2, 0 );
					
				}glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
		}glPopMatrix();
	
	restorePerspectiveProjection();
}

/************************************************************
	dibujado de la pantalla de game over con la pista de findo
*************************************************************/
void displayGameOverScreen(){
	
	// se liberan los recursos del sonido que ya no se utiliza
	if( gGAMEOVER_SOUND and gGAMEOVER_SOUND->isFinished() ){
		gGAMEOVER_SOUND->drop();
		gGAMEOVER_SOUND = NULL;
	}
	
	// se actualiza la posicion y direccion de la camara
	// util solo en el "modo debug"
	updateCameraLookAt();
	
	// pinta el escenario (pista con todos los objetons en ella, con excepción de la nave)
	drawScene();
	
	// ---------------------------------------------------------------------
	// se pinta el cuadro de game over con los datos correspondientes
	// ---------------------------------------------------------------------
	
	stringstream ss;
	// preparacion para impresion en pantalla
	setOrthographicProjection();
		glPushMatrix();
		glLoadIdentity();
		glColor3f(CYAN);
		
		ss.str("");
		ss << "Score: " << gSCORE;
		renderBitmapStringProjection( 
			-42, -80, 0,
			ss.str().c_str()
		);
		
		if( gSCORE_STATE == TOP){
			ss.str("");
			ss << "NEW CHAMPION !!!";
			renderBitmapStringProjection( 
				-115, -115, 0,
				ss.str().c_str()
			);
			if( !gGAMEOVER_SOUND and !gCONGRATS_DONE ){
				gSOUND_ENGINE->play2D("../media/excellent.ogg");
				gCONGRATS_DONE = true;
			}
		}else if( gSCORE_STATE == TOP_10){
			ss.str("");
			ss << " TOP 10 SCORE!!";
			renderBitmapStringProjection( 
				-75, -115, 0,
				ss.str().c_str()
			);
			if( !gGAMEOVER_SOUND and !gCONGRATS_DONE ){
				gSOUND_ENGINE->play2D("../media/good.ogg");
				gCONGRATS_DONE = true;
			}
		}
		
		if( gSCORE_STATE != NONE){
			ss.str("");
			ss << "Enter your name";
			renderBitmapStringProjection( 
				-70, 40, 0,
				ss.str().c_str()
			);
			renderBitmapStringProjection( 
				-100, 70, 0,
				(string("Player: ")+gPLAYER_NAME).c_str()
			);
		}
		
		ss.str("");
		ss << "[ENTER] Back to main menu";
		renderBitmapStringProjection( 
			-gSCREEN.getW()/2+20, -gSCREEN.getH()/2+30, 0,
			ss.str().c_str()
		);
		
		ss.str("");
		ss << "[ESC] Exit";
		renderBitmapStringProjection( 
			-gSCREEN.getW()/2+20, -gSCREEN.getH()/2+53, 0,
			ss.str().c_str()
		);
		// fin de impresion en pantalla
		glPopMatrix();
		
		// se dibuja la imagen de fondo del game over
		// (solo ocupa una seccion central de la pantalla)
		glPushMatrix();{
			glLoadIdentity();
			glColor3f(BLUE);
			
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,gGAME_OVER_BG);
				glBegin(GL_QUADS);{
				
					glTexCoord2f(0,0);
					glVertex3f( -170,  130-30, 0);
					
					glTexCoord2f(0,1);
					glVertex3f( -170, -130-30, 0);
					
					glTexCoord2f(1,1);
					glVertex3f(  170, -130-30, 0);
					
					glTexCoord2f(1,0);
					glVertex3f(  170,  130-30, 0);
					
				}glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
		}glPopMatrix();
		
	restorePerspectiveProjection();
}

/************************************************************
	dibujado del juego en progreso
*************************************************************/
void playing(){
	// se actualiza la posicion y direccion de la camara
	// util solo en el "modo debug"
	updateCameraLookAt();
	
	// pinta el escenario
	drawScene();
	
	// en el modo debug se dibuja los limites reales de la nave para la deteccion de colision
	if( gDEBUG_MODE ){
		drawCarCollisionArea();
	}
	
	// dibuja la nave en la posicion adecuada
	drawPositionedCar();
	
	//	==============================
	//		impresion en pantalla
	//	==============================
	
	// preparacion para impresion en pantalla
	setOrthographicProjection();
		glPushMatrix();
		glLoadIdentity();
		glColor3f(CYAN);
		
		// imprime datos del juego
		printGameData();
		
		// fin de impresion en pantalla
		glPopMatrix();
	restorePerspectiveProjection();
	
	// se disparan los efectos correspondientes segun las colisiones detectadas
	collisionHandler();
}

/************************************************************
	Funcion de control del estado "in game" (mirar primero la funcion display)
*************************************************************/
void displayInGame() {
	
	// segun el estado actual del juego
	switch( gIN_GAME_STATE ){
		
		// despliegue de las instrucciones
		case INSTRUCTIONS:{
			diplayInstructions();
		} break;
		
		// se realizan las preparaciones necesarias para ingresar al estado PLAYING
		case GAME_INIT:{
			// se sigue mostrando la pantalla de instrucciones durante un frame mas
			diplayInstructions();
			// el estado actual se pasa a PLAYING
			gIN_GAME_STATE = PLAYING;
			// se setean variables entre otras cosas
			gameInitialization();
		} break;
		
		// despliegue del juego en si
		case PLAYING:{
			playing();
		} break;
		
		// se realizan las preparaciones necesarias para ingresar al estado GAME_OVER_INIT
		case GAME_OVER_INIT:{
			// se imprime la pantalla de game over
			displayGameOverScreen();
			// extraccion del archivo con el top 10
			gRANKING.retrieveData();
			// se setea gSCORE_STATE segun el "status" del score con respecto al top 10
			if(gRANKING.isHighestScore(gSCORE)){
				gSCORE_STATE = TOP;
			}else if(gRANKING.isTop10(gSCORE)){
				gSCORE_STATE = TOP_10;
			}else{
				gSCORE_STATE = NONE;
			}
			// el estado actual se pasa a GAME_OVER
			gIN_GAME_STATE = GAME_OVER;
			// se reproduce el sonido de game over
			gGAMEOVER_SOUND = gSOUND_ENGINE->play2D("../media/gameover.ogg", false, false, true);
		} break;
		
		// despliegue de la pantalla de game over
		case GAME_OVER:{
			displayGameOverScreen();
		} break;
		
		// finalizacion del game over
		case GAME_OVER_END:{
			// si se ha ingresado algun texto...
			if( gPLAYER_NAME != "" ){
				// ... se inserta el nuevo score en el ranking
				// (si no cae entre los diez primeros no se tiene en cuenta)
				gRANKING.insert(gPLAYER_NAME,gSCORE);
				// se graban los nuevos datos en el archivo de ranking
				gRANKING.setData();
			}
			// se detiene la musica que se utiliza mientras se juega
			gINGAME_MUSIC->setIsPaused();
			// se reproduce la musica del menu desde el inicio
			gMENU_MUSIC->setPlayPosition(0);
			gMENU_MUSIC->setIsPaused(false);
			// se preparan los estado para pasar al menu principal
			gGENERAL_STATE = MAIN_MENU;
			gIN_GAME_STATE = INSTRUCTIONS;
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
	
	// en el modo debug se imprimen algunas variables internas de interez
	if(gDEBUG_MODE){
		setOrthographicProjection();
		glPushMatrix();{
			glLoadIdentity();
			glColor3f(GREEN);
			// imprime datos relevantes
			printVariables();
		// fin de impresion en pantalla
		}glPopMatrix();
		restorePerspectiveProjection();
	}
	
	// se llama a la funcion correspondiente segun el estado del juego
	// el cual puede ser "menu principal" o "in game"
	// IN_GAME tiene nuevamente otros sub-estados
	switch( gGENERAL_STATE ){
		case MAIN_MENU:{
			displayMainMenu();
		} break;
		
		case IN_GAME:{
			displayInGame();
		} break;
		
		case EXIT:{
			exit(0);
		} break;
	}
	
	// en el modo debug se imprimen algunas variables internas de interez
	if(gDEBUG_MODE){
		setOrthographicProjection();
		glPushMatrix();{
			glLoadIdentity();
			glColor3f(GREEN);
			// imprime datos relevantes
			printVariables();
		// fin de impresion en pantalla
		}glPopMatrix();
		restorePerspectiveProjection();
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

















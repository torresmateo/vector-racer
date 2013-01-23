
void displayMainMenu() {
	stringstream ss;
	
	// preparacion para impresion en pantalla
	// setOrthographicProjection();
		// glPushMatrix();{
			// glLoadIdentity();
			
			// glColor3f(GREEN);
			
			// ss << "[ENTER] ";
			// ss << "Play!!";
			// renderBitmapStringProjection( 
				// gSCREEN.getW()/2.0, gSCREEN.getH()/2.0, 0,
				// ss.str().c_str()
			// );

			// ss.str("");
			// ss << "[ESC] exit";
			// renderBitmapStringProjection( 
				// 20, 20, 0,
				// ss.str().c_str()
			// );
			
		////fin de impresion en pantalla
		// }glPopMatrix();
	// restorePerspectiveProjection();
	
	gRANKING.draw();
	
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

void diplayInstructions(){
	stringstream ss;
	
	// preparacion para impresion en pantalla
	setOrthographicProjection();
		glPushMatrix();
		glLoadIdentity();
		// glColor3f(GREEN);
		
		// ss << "Instrucciones";
		// renderBitmapStringProjection( 
			// gSCREEN.getW()/2.0, gSCREEN.getH()/2.0, 0,
			// ss.str().c_str()
		// );
		
		// ss.str("");
		// ss << "[ENTER] Start when ready";
		// renderBitmapStringProjection( 
			// gSCREEN.getW()*0.7, gSCREEN.getH()*0.7, 0,
			// ss.str().c_str()
		// );
		
		// ss.str("");
		// ss << "[ESC] Back to main menu";
		// renderBitmapStringProjection( 
			// gSCREEN.getW()*0.7, gSCREEN.getH()*0.7-25, 0,
			// ss.str().c_str()
		// );
		
		// fin de impresion en pantalla
		glPopMatrix();
		
		glPushMatrix();{
			glLoadIdentity();
			glColor3f(BLUE);
			
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
		
		// ss << "GAME OVER";
		// renderBitmapStringProjection( 
			// gSCREEN.getW()/2.0, gSCREEN.getH()/2.0, 0,
			// ss.str().c_str()
		// );
		
		ss.str("");
		ss << "Score: " << gSCORE;
		renderBitmapStringProjection( 
			-42, -80, 0,
			ss.str().c_str()
		);
		
		if( gSCORE_STATE == TOP){
			ss.str("");
			ss << "NEW HIGHTEST SCORE !!!";
			renderBitmapStringProjection( 
				-115, -115, 0,
				ss.str().c_str()
			);
		}else if( gSCORE_STATE == TOP_10){
			ss.str("");
			ss << " TOP 10 SCORE!!";
			renderBitmapStringProjection( 
				-75, -115, 0,
				ss.str().c_str()
			);
			
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
		
		case GAME_INIT:{
			diplayInstructions();
			gIN_GAME_STATE = PLAYING;
			gameInitialization();
		} break;
		
		case PLAYING:{
			playing();
		} break;
		
		case GAME_OVER_INIT:{
			displayGameOverScreen();
			gRANKING.retrieveData();
			if(gRANKING.isHighestScore(gSCORE)){
				gSCORE_STATE = TOP;
			}else if(gRANKING.isTop10(gSCORE)){
				gSCORE_STATE = TOP_10;
			}else{
				gSCORE_STATE = NONE;
			}
			gIN_GAME_STATE = GAME_OVER;
		} break;
		
		case GAME_OVER:{
			displayGameOverScreen();
		} break;
		
		case GAME_OVER_END:{
			if( gPLAYER_NAME != "" ){
				gRANKING.insert(gPLAYER_NAME,gSCORE);
				gRANKING.setData();
			}
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




















void processInput() {

	/***********************************
		Seccion con posibilidad de ninguna tecla presionada
	************************************/
	
	// en caso de que la nave no se mueva lateralmente se contraresta la inclinacion
	if( 
		(
			( !gKEYBOARD.specialKeyPressed(GLUT_KEY_RIGHT) and !gKEYBOARD.specialKeyPressed(GLUT_KEY_LEFT) )
			or
			( gKEYBOARD.specialKeyPressed(GLUT_KEY_RIGHT) and gKEYBOARD.specialKeyPressed(GLUT_KEY_LEFT) )
		)
		and 
		gCAR_TILT 
	){
		if( 0 < gCAR_TILT )
			gCAR_TILT -= TILT_SPEED;
		if( gCAR_TILT < 0 )
			gCAR_TILT += TILT_SPEED;
	}
	
	/***********************************
		Seccion de tecla(s) presionada(s)
	***********************************/
	if( !gKEYBOARD.keyPressed() )
		return;
	
	// ===== miscelaneas ===========
	
	if( gKEYBOARD.asciiKeyPressed('w') ){
		gCAM_POS += gCAM_DIR*gCAM_TRASNLATE_SPEED;
	}
	if( gKEYBOARD.asciiKeyPressed('a') ){
		Vector3D auxCamDir(gCAM_DIR);
		
		double angleXZ = auxCamDir.getAngleXZ()-HALF_PI;
		auxCamDir.setAngleXZ( HALF_PI );
		auxCamDir.setAngleYZ( HALF_PI );
		auxCamDir.setAngleXZ( angleXZ );
		
		gCAM_POS += auxCamDir*gCAM_TRASNLATE_SPEED;
	}
	
	if( gKEYBOARD.asciiKeyPressed('s') ){
		gCAM_POS -= gCAM_DIR*gCAM_TRASNLATE_SPEED;
	}
	
	if( gKEYBOARD.asciiKeyPressed('d') ){
		Vector3D auxCamDir(gCAM_DIR);
		
		double angleXZ = auxCamDir.getAngleXZ()+HALF_PI;
		auxCamDir.setAngleXZ( HALF_PI );
		auxCamDir.setAngleYZ( HALF_PI );
		auxCamDir.setAngleXZ( angleXZ );
		
		gCAM_POS += auxCamDir*gCAM_TRASNLATE_SPEED;
	}
	
	if( gKEYBOARD.asciiKeyPressed('r') ){
		gCAM_POS.setXYZ(0,0,0);
	}
	
	// ===== end miscelaneas =======
	
	
	switch( gGENERAL_STATE ){
		//==================================
		// controles para el menu principal
		case MAIN_MENU:{
			if( gKEYBOARD.asciiKeyPressed(ESC) ){
				gGENERAL_STATE = EXIT;
			}
			if( gKEYBOARD.asciiKeyPressed(SPACE)){
				gKEYBOARD.removeAsciiKey(SPACE);
				gGENERAL_STATE = GAME_INIT;
			}
		}break;
		
		//==================================
		// controles in game
		case IN_GAME:{
			switch( gIN_GAME_STATE ){
				//==================================
				// seccion de instrucciones
				case INSTRUCTIONS:{
					if( gKEYBOARD.asciiKeyPressed(SPACE) ){
						gKEYBOARD.removeAsciiKey(SPACE);
						gIN_GAME_STATE = PLAYING;
					}
					if( gKEYBOARD.asciiKeyPressed(ESC) ){
						gKEYBOARD.removeAsciiKey(ESC);
						gGENERAL_STATE = MAIN_MENU;
					}
				}break;
				
				//==================================
				// controles del juego en progreso
				case PLAYING:{
					if( gKEYBOARD.specialKeyPressed(GLUT_KEY_LEFT) and !gKEYBOARD.specialKeyPressed(GLUT_KEY_RIGHT) ){
						if( fabs(gCAR_TILT-TILT_SPEED) < 45 )
							gCAR_TILT -= TILT_SPEED;
						gCAR_POS.setX( gCAR_POS.getX()+gCAR_LATERAL_SPEED);
						if(gCAR_POS.getX() > ROAD_LIMIT-CAR_WIDTH/2.0)
							gCAR_POS.setX(ROAD_LIMIT-CAR_WIDTH/2.0);
					}
					
					if( gKEYBOARD.specialKeyPressed(GLUT_KEY_RIGHT) and !gKEYBOARD.specialKeyPressed(GLUT_KEY_LEFT) ){
						if( fabs(gCAR_TILT+TILT_SPEED) < 45 )
							gCAR_TILT += TILT_SPEED;
						gCAR_POS.setX( gCAR_POS.getX()-gCAR_LATERAL_SPEED);
						if(gCAR_POS.getX() < -ROAD_LIMIT+CAR_WIDTH/2.0)
							gCAR_POS.setX(-ROAD_LIMIT+CAR_WIDTH/2.0);
					}
					
					if( gKEYBOARD.asciiKeyPressed(ESC) ){
						gKEYBOARD.removeAsciiKey(ESC);
						gIN_GAME_STATE = GAME_OVER;
					}
					
				}break;
				
				//==================================
				// controles del estado game over
				case GAME_OVER:{
					if( gKEYBOARD.asciiKeyPressed(SPACE) ){
						gKEYBOARD.removeAsciiKey(SPACE);
						gGENERAL_STATE = MAIN_MENU;
						gIN_GAME_STATE = INSTRUCTIONS;
					}
					if( gKEYBOARD.asciiKeyPressed(ESC) ){
						gKEYBOARD.removeAsciiKey(ESC);
						gGENERAL_STATE = EXIT;
					}
				}break;
			}
		}break;
		
		// en los casos siguientes no se realiza control de teclas presionadas
		case GAME_INIT:{}break;
		case EXIT:{}break;
		
	}
	
	/****************************************/
	/*
	if( !gKEY.Q and !gKEY.E and gCAR_TILT ){
		if( 0 < gCAR_TILT )
			gCAR_TILT -= TILT_SPEED;
		if( gCAR_TILT < 0 )
			gCAR_TILT += TILT_SPEED;
	}
	
	if( gKEY.PRESSED ){
	
		if( gKEY.Q ){
			if( fabs(gCAR_TILT-TILT_SPEED) < 45 )
				gCAR_TILT -= TILT_SPEED;
			gCAR_POS.setX( gCAR_POS.getX()+gCAR_LATERAL_SPEED);
			if(gCAR_POS.getX() > ROAD_LIMIT-CAR_WIDTH/2.0)
				gCAR_POS.setX(ROAD_LIMIT-CAR_WIDTH/2.0);
		}
		
		if( gKEY.E ){
			if( fabs(gCAR_TILT+TILT_SPEED) < 45 )
				gCAR_TILT += TILT_SPEED;
			gCAR_POS.setX( gCAR_POS.getX()-gCAR_LATERAL_SPEED);
			if(gCAR_POS.getX() < -ROAD_LIMIT+CAR_WIDTH/2.0)
				gCAR_POS.setX(-ROAD_LIMIT+CAR_WIDTH/2.0);
		}
		
		if( gKEY.W ){
			gCAM_POS += gCAM_DIR*gCAM_TRASNLATE_SPEED;
		}
		
		if( gKEY.A ){
			Vector3D auxCamDir(gCAM_DIR);
			
			double angleXZ = auxCamDir.getAngleXZ()-HALF_PI;
			auxCamDir.setAngleXZ( HALF_PI );
			auxCamDir.setAngleYZ( HALF_PI );
			auxCamDir.setAngleXZ( angleXZ );
			
			gCAM_POS += auxCamDir*gCAM_TRASNLATE_SPEED;
		}
		
		if( gKEY.S ){
			gCAM_POS -= gCAM_DIR*gCAM_TRASNLATE_SPEED;
		}
		
		if( gKEY.D ){
			Vector3D auxCamDir(gCAM_DIR);
			
			double angleXZ = auxCamDir.getAngleXZ()+HALF_PI;
			auxCamDir.setAngleXZ( HALF_PI );
			auxCamDir.setAngleYZ( HALF_PI );
			auxCamDir.setAngleXZ( angleXZ );
			
			gCAM_POS += auxCamDir*gCAM_TRASNLATE_SPEED;
		}
		
		
		if( gKEY.Z ){
			gCAR_SPEED = 0.49f;
			gFLOAT_DEBUGy += 0.005;
		}
		if( gKEY.C ){
			gFLOAT_DEBUGy -= 0.005;
			gCAR_SPEED = 0;
			gGENERAL_STATE = GAME_INIT;
		}
		
		
		if( gKEY.ESC ){
			exit(0);
		}
	}*/
}






































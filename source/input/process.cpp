


void processInput() {
	
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
		
		if( gKEY.W ){
			gCAM_POS += gCAM_DIR*gCAM_TRASNLATE_SPEED;
		}
		
		if( gKEY.E ){
			if( fabs(gCAR_TILT+TILT_SPEED) < 45 )
				gCAR_TILT += TILT_SPEED;
			gCAR_POS.setX( gCAR_POS.getX()-gCAR_LATERAL_SPEED);
			if(gCAR_POS.getX() < -ROAD_LIMIT+CAR_WIDTH/2.0)
				gCAR_POS.setX(-ROAD_LIMIT+CAR_WIDTH/2.0);
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
		}
		
		
		if( gKEY.ESC ){
			exit(0);
		}
	}
}

void collisionHandler(){
	int CurentIndex = gTUNNEL_PATH.getCurrentSegmentsIndex()+2;
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
	}
}




































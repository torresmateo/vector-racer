


void processInput() {
	if( gKEY.PRESSED ){
	
		if( gKEY.Q ){
			gCAR_POS.setX( gCAR_POS.getX()+gCAR_LATERAL_SPEED);
			gFLOAT_DEBUG -= 0.005;
		}
		
		if( gKEY.W ){
			gCAM_POS += gCAM_DIR*gCAM_TRASNLATE_SPEED;
		}
		
		if( gKEY.E ){
			gCAR_POS.setX( gCAR_POS.getX()-gCAR_LATERAL_SPEED);
			gFLOAT_DEBUG += 0.005;
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

void colisionHandler(){
	int CurentIndex = gTUNNEL_PATH.getCurrentSegmentsIndex()+2;
	PathSection currentSection(gTUNNEL_PATH.getCurrentSection());
	
	if(currentSection.thereIsWhiteSphere(CurentIndex) and currentSection.getWhiteSphere(CurentIndex)->isCollision()){
		gDEBUG = "restar vida";
	}else gDEBUG = " - ";
}




































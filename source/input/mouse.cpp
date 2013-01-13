


void mouseActiveMove(int mouseX, int mouseY) {
	Vector2D newMouse( mouseX, mouseY );
	Vector2D deltaMouse( newMouse - gMOUSE );
	gMOUSE = newMouse;
	
	gCAM_DIR.rotateXZ( deltaMouse.getX()*gCAM_ROTATE_SPEED );
	gCAM_DIR.rotateYH( deltaMouse.getY()*gCAM_ROTATE_SPEED );
}


void mouseClick(int button, int state, int mouseX, int mouseY) {
	gMOUSE.setXY( mouseX, mouseY );
}





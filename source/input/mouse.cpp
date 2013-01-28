

// funcion registrada para ser llamada al mover el mouse mientras se clickea
void mouseActiveMove(int mouseX, int mouseY) {
	// si se esta en el modo debug 
	// se mueve la direccion de la camara segun el movimiento realizado con el mouse
	if(gDEBUG_MODE){
		Vector2D newMouse( mouseX, mouseY );
		Vector2D deltaMouse( newMouse - gMOUSE );
		gMOUSE = newMouse;
		
		gCAM_DIR.rotateXZ( deltaMouse.getX()*gCAM_ROTATE_SPEED );
		gCAM_DIR.rotateYH( deltaMouse.getY()*gCAM_ROTATE_SPEED );
	}
}

// funcion registrada para ser llamada al hacer click
void mouseClick(int button, int state, int mouseX, int mouseY) {
	// se asigna la nueva "posicion inicial" del mouse
	gMOUSE.setXY( mouseX, mouseY );
}





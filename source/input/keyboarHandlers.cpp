

// funcion registrada para ser llamada al presionar una tecla "ascii"
void pressNormalKey(unsigned char key, int mouseX, int mouseY) {
	// se registra la tecla presionada
	gKEYBOARD.insertAsciiKey(key);
}

// funcion registrada para ser llamada al presionar una tecla especial
void pressSpecialKey(int key, int mouseX, int mouseY) {
	// se registra la tecla presionada
	gKEYBOARD.insertSpecialKey(key);
}


// funcion registrada para ser llamada al liberar una tecla "ascii"
void releaseNormalKey(unsigned char key, int mouseX, int mouseY) {
	// se remueve la tecla liberada
	gKEYBOARD.removeAsciiKey(key);
}

// funcion registrada para ser llamada al liberar una tecla especial
void releaseSpecialKey(int key, int mouseX, int mouseY) {
	// se remueve la tecla liberada
	gKEYBOARD.removeSpecialKey(key);
}





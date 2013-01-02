




void pressNormalKey(unsigned char key, int mouseX, int mouseY) {
	switch( key ){
		case 'q': gKEY.Q = true; gKEY.PRESSED++; break;
		case 'w': gKEY.W = true; gKEY.PRESSED++; break;
		case 'e': gKEY.E = true; gKEY.PRESSED++; break;
		case 'a': gKEY.A = true; gKEY.PRESSED++; break;
		case 's': gKEY.S = true; gKEY.PRESSED++; break;
		case 'd': gKEY.D = true; gKEY.PRESSED++; break;
		case 27 : gKEY.ESC = true; gKEY.PRESSED++; break;
	}
}


void pressSpecialKey(int key, int mouseX, int mouseY) {
	// switch( key ){
		// case ??: gKEY.?? = true; gKEY.PRESSED++; break;
	// }
}


void releaseNormalKey(unsigned char key, int mouseX, int mouseY) {
	switch( key ){
		case 'q': gKEY.Q = false; gKEY.PRESSED--; break;
		case 'w': gKEY.W = false; gKEY.PRESSED--; break;
		case 'e': gKEY.E = false; gKEY.PRESSED--; break;
		case 'a': gKEY.A = false; gKEY.PRESSED--; break;
		case 's': gKEY.S = false; gKEY.PRESSED--; break;
		case 'd': gKEY.D = false; gKEY.PRESSED--; break;
		case 27 : gKEY.ESC = false; gKEY.PRESSED--; break;
	}
}

void releaseSpecialKey(int key, int mouseX, int mouseY) {
	// switch( key ){
		// case ??: gKEY.?? = false; gKEY.PRESSED--; break;
	// }
}





























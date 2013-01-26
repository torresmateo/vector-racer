


void pressNormalKey(unsigned char key, int mouseX, int mouseY) {
	gKEYBOARD.insertAsciiKey(key);
}

void pressSpecialKey(int key, int mouseX, int mouseY) {
	gKEYBOARD.insertSpecialKey(key);
}



void releaseNormalKey(unsigned char key, int mouseX, int mouseY) {
	gKEYBOARD.removeAsciiKey(key);
}

void releaseSpecialKey(int key, int mouseX, int mouseY) {
	gKEYBOARD.removeSpecialKey(key);
}





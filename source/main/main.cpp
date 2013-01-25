
void FPSLock(int millisec) {
	glutTimerFunc(millisec, FPSLock, millisec);gDEBUG = gKEYBOARD.toString();
	glutPostRedisplay();
}

void increaseSpeed(int millisec){
	glutTimerFunc(millisec, increaseSpeed, millisec);
	if( gCAR_SPEED*1.1 <= 1 )
		gCAR_SPEED *= 1.1;
}

void scorePP(int millisec){
	if(gIN_GAME_STATE!=PLAYING)
		return;
	gSCORE ++;
	glutTimerFunc(millisec, scorePP, millisec);
}

void carGhostHandler(int millisec){
	if(!millisec){
		gCAR_GHOST = 11;
		glutTimerFunc(150, carGhostHandler, 150);
	}else{
		gCAR_GHOST--;
		if(gCAR_GHOST)
			glutTimerFunc(millisec, carGhostHandler, millisec);
	}
	
}

int main(int argc, char **argv) {
	srand ( time(NULL) );
	loadPath();
	
	ISoundEngine* soundEngine = createIrrKlangDevice();
	
	gINGAME_MUSIC = soundEngine->play2D("../media/ingame.ogg", true, true, true);
	gINGAME_MUSIC->setVolume(0.6);
	
	gMENU_MUSIC = soundEngine->play2D("../media/menu.ogg", true, true, true);
	gMENU_MUSIC->setVolume(0.6);
	
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowPosition(550,150);
	glutInitWindowSize(800,600);
	glutCreateWindow("Underground Race");
	

	glEnable(GL_DEPTH_TEST);
	
	gFIGHTER_MODEL=gOBJ_LOADER.load("fighter.obj");
	gTUNNEL_TEXTURE = gOBJ_LOADER.loadSingleTexture("tunnel.bmp");
	gMAIN_MENU_BG = gOBJ_LOADER.loadSingleTexture("main-menu-background.bmp");
	gINSTRUCTIONS_BG = gOBJ_LOADER.loadSingleTexture("instructions-background.bmp");
	gGAME_OVER_BG = gOBJ_LOADER.loadSingleTexture("game-over-background.bmp");
	
	
	// register callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	// glutIdleFunc(display);
	glutTimerFunc(30,FPSLock,30);
	glutTimerFunc(10000,increaseSpeed,10000);
	
	glutIgnoreKeyRepeat(1);
	// keyboard register callbacks
	glutKeyboardFunc(pressNormalKey);
	glutSpecialFunc(pressSpecialKey);
	glutKeyboardUpFunc(releaseNormalKey);
	glutSpecialUpFunc(releaseSpecialKey);
	
	// mouse register callbacks
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseActiveMove);
	
	gMENU_MUSIC->setIsPaused(false);
	// enter GLUT event processing cycle
	glutMainLoop();
	
	soundEngine->drop();
	return 1;
}


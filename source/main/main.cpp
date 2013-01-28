
//limitador de FOS
void FPSLock(int millisec) {
	glutTimerFunc(millisec, FPSLock, millisec);gDEBUG = gKEYBOARD.toString();
	glutPostRedisplay();
}

//aumenta la velocidad en un factor de 1.1
void increaseSpeed(int millisec){
	glutTimerFunc(millisec, increaseSpeed, millisec);
	if( gCAR_SPEED*1.1 <= 1 )
		gCAR_SPEED *= 1.1;
}

//sumador de puntos
void scorePP(int millisec){
	if(gIN_GAME_STATE!=PLAYING)//si no estamos en el juego, no necesitamos sumar puntos
		return;
	if(gDEBUG_MODE){// si estamos en modo debug se resetea el score para evitar trampas 
		gSCORE = 0;
		return;
	}
		
	//si estamos en juego y fuera del modo debug, se suman puntos
	gSCORE ++;
	glutTimerFunc(millisec, scorePP, millisec);
}

//manejador del estado post colisión
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

//función principal del programa
int main(int argc, char **argv) {
	srand ( time(NULL) );
	//carga del path inicial predefinido
	loadPath();
	
	//inicialización del sonido
	gSOUND_ENGINE = createIrrKlangDevice();
	
	//carga de las músicas de fondo
	gINGAME_MUSIC = gSOUND_ENGINE->play2D("../media/ingame.ogg", true, true, true);
	gMENU_MUSIC = gSOUND_ENGINE->play2D("../media/menu.ogg", true, true, true);
	
	//configuración del volumen
	gINGAME_MUSIC->setVolume(0.45);
	gMENU_MUSIC->setVolume(0.45);
	
	//configuración inicial de la ventana utilizando GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("Underground Race");
	glEnable(GL_DEPTH_TEST);
	
	//carga del modelo de la nave
	gFIGHTER_MODEL=gOBJ_LOADER.load("fighter.obj");

	//carga de las texturas
	
	//buffer para el nombre del archivo de las texturas
	string filename;
	//buffer para conversion de entero a string
	std::ostringstream itoa;

	//carga de texturas del tunel
	for(int i = 0 ; i < TEX_SEQ_QTY ; i++){
		itoa << i;
		filename.assign("tunnel");
		filename.append(itoa.str());
		filename.append(".bmp");
		gTUNNEL_TEXTURE[i] = gOBJ_LOADER.loadSingleTexture(filename.c_str());
		filename.assign("tunnelFloor");
		filename.append(itoa.str());
		filename.append(".bmp");
		gTUNNEL_FLOOR_TEXTURE[i] = gOBJ_LOADER.loadSingleTexture(filename.c_str());
		itoa.clear();
		itoa.str("");
	}
	//carga de texturas de los obstaculos
	gCUBE_TEXTURE = gOBJ_LOADER.loadSingleTexture("cube.bmp");
	gMAIN_MENU_BG = gOBJ_LOADER.loadSingleTexture("main-menu-background.bmp");
	gINSTRUCTIONS_BG = gOBJ_LOADER.loadSingleTexture("instructions-background.bmp");
	gGAME_OVER_BG = gOBJ_LOADER.loadSingleTexture("game-over-background.bmp");
	drawCar();
	
	//configuracion de las funciones de GLUT
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	// glutIdleFunc(display);
	glutTimerFunc(30,FPSLock,30);
	glutTimerFunc(10000,increaseSpeed,10000);
	
	glutIgnoreKeyRepeat(1);
	//funciones del teclado
	glutKeyboardFunc(pressNormalKey);
	glutSpecialFunc(pressSpecialKey);
	glutKeyboardUpFunc(releaseNormalKey);
	glutSpecialUpFunc(releaseSpecialKey);
	
	//funciones del mouse
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseActiveMove);
	
	gMENU_MUSIC->setIsPaused(false);
	//inicializacion del main loop de GLUT
	glutMainLoop();
	
	gSOUND_ENGINE->drop();
	return 1;
}


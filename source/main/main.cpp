
void timerCB(int millisec) {
	glutTimerFunc(millisec, timerCB, millisec);DEBUG(gCAR_SPEED);
	glutPostRedisplay();
}

void increaseSpeed(int millisec){
	glutTimerFunc(millisec, increaseSpeed, millisec);
	if( gCAR_SPEED*1.1 <= 1 )
		gCAR_SPEED *= 1.1;
}

void scorePP(int millisec){
	glutTimerFunc(millisec, scorePP, millisec);
	gSCORE ++;
}

objLoader obj;
int main(int argc, char **argv) {
	srand ( time(NULL) );
	
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowPosition(550,150);
	glutInitWindowSize(800,600);
	glutCreateWindow("Underground Race");
	

	glEnable(GL_DEPTH_TEST);
	
	//Fer: esto dejo por el momento porque me es super util descomentar una linea y comentar la otra para cambiar el objeto del modelo, el resto de los comentarios ya borre
	cube=obj.load("cardassiangalor.obj");	//load the test.obj file
	//cube=obj.load("beetle.obj");	//load the test.obj file
	//scube=obj.load("test.obj");	//load the test.obj file
	
	loadPath();
	
	// register callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	// glutIdleFunc(display);
	glutTimerFunc(30,timerCB,30);
	glutTimerFunc(10000,increaseSpeed,10000);
	glutTimerFunc(100,scorePP,100);
	
	glutIgnoreKeyRepeat(1);
	// keyboard register callbacks
	glutKeyboardFunc(pressNormalKey);
	glutSpecialFunc(pressSpecialKey);
	glutKeyboardUpFunc(releaseNormalKey);
	glutSpecialUpFunc(releaseSpecialKey);
	
	// mouse register callbacks
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseActiveMove);
	
	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}


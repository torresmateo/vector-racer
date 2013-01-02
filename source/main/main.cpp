
int main(int argc, char **argv) {
	
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(550,150);
	glutInitWindowSize(800,600);
	glutCreateWindow("Titulo de la ventana");
	
	// register callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	glutIdleFunc(display);
	
	glutIgnoreKeyRepeat(1);
	// keyboard register callbacks
	glutKeyboardFunc(pressNormalKey);
	glutSpecialFunc(pressSpecialKey);
	glutKeyboardUpFunc(releaseNormalKey);
	glutSpecialUpFunc(releaseSpecialKey);
	
	// mouse register callbacks
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseActiveMove);
	
	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}


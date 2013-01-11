

int main(int argc, char **argv) {
	
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
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
	//glShadeModel(GL_SMOOTH);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);
	
	system("pwd");
	printf("hola");
	glEnable(GL_DEPTH_TEST);
	cube=loadObject("cube.obj");	//load the test.obj file
	//glEnable(GL_LIGHTING);	//we enable lighting, to make the 3D object to 3D
	//glEnable(GL_LIGHT0);
	//float col[]={1.0,1.0,1.0,1.0};	//light color is white
	//glLightfv(GL_LIGHT0,GL_DIFFUSE,col);

	//cube = loadObject("cube.obj");
	loadPath();
	
	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}


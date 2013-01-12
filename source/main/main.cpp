
objLoader obj;
int main(int argc, char **argv) {
	srand ( time(NULL) );
	
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowPosition(550,150);
	glutInitWindowSize(800,600);
	glutCreateWindow("Underground Race");
	
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
	
	glEnable(GL_DEPTH_TEST);
	
	//system("pwd");
	
	
	//glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    float col[]={1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0,GL_DIFFUSE,col);
	
	
	//cube=obj.load("cardassiangalor.obj");	//load the test.obj file
	cube=obj.load("beetle.obj");	//load the test.obj file
	
	loadPath();
	
	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}



objLoader obj;
int main(int argc, char **argv) {
	srand ( time(NULL) );
	
	// init GLUT and create window
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(550,150);
	glutInitWindowSize(800,600);
	glutCreateWindow("Underground Race");
	




/*
	
	  GLfloat light_ambient[] = { 0.75, 0.75, 0.75, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };

    glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
	
*/
	// OpenGL init
	//glShadeModel(GL_SMOOTH);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_DEPTH_TEST);
	
	//system("pwd");
	
	
	glEnable(GL_LIGHTING);
    //glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    float col[]={1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0,GL_DIFFUSE,col);
	glLightfv(GL_LIGHT0,GL_AMBIENT,col);
	glLightfv(GL_LIGHT0,GL_SPECULAR,col);
	
	cube=obj.load("cardassiangalor.obj");	//load the test.obj file
	//cube=obj.load("beetle.obj");	//load the test.obj file
	//scube=obj.load("test.obj");	//load the test.obj file
	
	loadPath();
	









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
	
	

	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}


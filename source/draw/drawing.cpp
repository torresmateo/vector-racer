

void tube(GLfloat radius, GLfloat segment_length) {
    glPolygonMode(GL_BACK, GL_NONE);
    glPolygonMode(GL_FRONT, GL_FILL);
    
    glPushMatrix(); {
        GLfloat z1 = 0.0;
        GLfloat z2 = segment_length;
        
        GLfloat y_offset = 0.0;
        GLfloat y_change = 0.00;
        
        int i = 0;
        int j = 0;
        for (j = 0; j < 20; j++) {
            glPushMatrix(); {
                glBegin(GL_TRIANGLE_STRIP); {
                    for (i = 360; i >= 0; i--) {
                        GLfloat theta = i * PI/180;
                        GLfloat x = radius * cos(theta);
                        GLfloat y = radius * sin(theta) + y_offset;
                        
                        glVertex3f(x, y, z1);
                        glVertex3f(x, y, z2);
                    }
                } glEnd();
            } glPopMatrix();
            
            // attach the front of the next segment to the back of the previous
            z1 = z2;
            z2 += segment_length;
            
            // make some other adjustments
            y_offset += y_change;
        }
    } glPopMatrix();
}


void drawCar(){
	Vector3D auxVec(gCAM_DIR);
	// double tempAngle;
	glColor3f(RED);
	
	// actualizar la posicion del auto
	gCAR_POS = gCAM_POS + gCAM_DIR*4.0f;
	gCAR_POS.setY( gCAR_POS.getY()-1.0f );
	
	glPushMatrix();
		glTranslatef(GET_TRIPLET(gCAR_POS));
		glRotatef(
			RADIANS_TO_DEGREES(-gCAM_DIR.getAngleXZ()+HALF_PI),
			0.0f, 1.0f, 0.0f
		);
		glRotatef(
			RADIANS_TO_DEGREES(gCAM_DIR.getAngleYH()-HALF_PI),
			1.0f, 0.0f, 0.0f
		);
		glTranslatef(gCAR_LATERAL_SHIFT,0.0f,0.0f);
		glutWireCone(0.08f,0.5f,10,2);
	glPopMatrix();
}

/************************************************************
	funcion para pintar el escenario
*************************************************************/
void drawScene() {
	// Draw ground
/*	glColor3f(0.8f, 0.8f, 0.8f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
*//*
	// Draw 36 SnowMen
	for(int i = -3; i < 3; i++)
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0f, 0.0f, j * 10.0f);
			drawSnowMan();
			glPopMatrix();
		}
*/
	tube(1.0,3.0);
	drawCar();
}

/************************************************************
	dibuja un munheco de nieve
*************************************************************/
void drawSnowMan() {

	// glScalef(scale, scale, scale);
	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

	// Draw Head
	glTranslatef(0.0f, 0.95f, 0.0f);
	glutSolidSphere(0.25f,20,20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f,0.5f,10,2);

	glColor3f(1.0f, 1.0f, 1.0f);

}


/************************************************************
	
*************************************************************/
void renderBitmapString(
		float x, float y, float z,
		void *font,
		const char *text) 
{
	glRasterPos3f(x, y,z);
	
	for(int i=0; text[i]; i++)
		glutBitmapCharacter(font, text[i]);
}


/************************************************************
	
*************************************************************/
void renderStrokeFontString(
		float x, float y, float z,
		void *font,
		const char *text)
{  
	glPushMatrix();
	glTranslatef(x, y,z);
	glScalef(0.002f, 0.002f, 0.002f);
	
	for(int i=0; text[i]; i++)
		glutStrokeCharacter(font, text[i]);
		
	glPopMatrix();
}


/************************************************************
	
*************************************************************/
void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, gSCREEN.getW(), gSCREEN.getH(), 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}


/************************************************************
	
*************************************************************/
void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

/************************************************************
	
*************************************************************/
void renderBitmapStringProjection( double x, double y, double z, const char* text ) {
	setOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(
		x,y,z,
		GLUT_BITMAP_HELVETICA_18,
		text
	);
	glPopMatrix();

	restorePerspectiveProjection();
}


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	






void customCylinder(
		GLfloat radius, 
		Vector3D posCenterIni, Vector3D normalIni, 
		Vector3D posCenterEnd, Vector3D normalEnd,
		int numSegment
	) {
	
    glPolygonMode(GL_BACK, GL_FILL);
    glPolygonMode(GL_FRONT, GL_LINE);
    
	GLfloat x, y, z, theta;
	Vector3D centerVector, a, b;
	
	if( normalIni.getX() == 0 and normalIni.getY() == 0 and normalIni.getZ() == 0 )
		normalIni.setZ(1);
	else
		normalIni.setNormalized();
	
	if( normalEnd.getX() == 0 and normalEnd.getY() == 0 and normalEnd.getZ() == 0 )
		normalEnd.setZ(1);
	else
		normalEnd.setNormalized();
	
	
	
	
    glPushMatrix();{
		
		glTranslatef(GET_TRIPLET(posCenterIni));
			
		Vector3D rotateAxis(0,0,1);
		rotateAxis = Vector3D::crossMultiply(rotateAxis,normalIni);
		
		glRotatef(
			RADIANS_TO_DEGREES(asin(rotateAxis.getMag())),
			GET_TRIPLET(rotateAxis)
		);
		
		for(int j=0; j<numSegment; j++){
			
			/**/glColor3f(RED);
			/**/glBegin(GL_LINE_STRIP); 
			/**//**/glVertex3f(0,0,0);
			/**//**/glVertex3f(GET_TRIPLET(posCenterEnd));
			/**/glEnd();
			
			glColor3f(BLUE);
			glBegin(GL_QUAD_STRIP);{
				for (int i = 0; i <= 360; i+=18) {
					theta = i * PI/180;
					x = radius * cos(theta);
					y = radius * sin(theta);
					z = 0;
					gDEBUG=doubleToStr(x);
					gDEBUG += ", ";
					
					glVertex3f(x, y, z);
					theta = (i-45) * PI/180;
					a = normalEnd.getUnitaryPerpendicularVector();
					b = Vector3D::crossMultiply(normalEnd,a);
					
					x = radius*cos(theta)*a.getX() + radius*sin(theta)*b.getX() + posCenterEnd.getX();
					y = radius*cos(theta)*a.getY() + radius*sin(theta)*b.getY() + posCenterEnd.getY();
					z = radius*cos(theta)*a.getZ() + radius*sin(theta)*b.getZ() + posCenterEnd.getZ();
					gDEBUG += doubleToStr(x);
					glVertex3f(x, y, z);	
				}
			}glEnd();
			
			glTranslatef(GET_TRIPLET(posCenterEnd));
			
			Vector3D rotateAxis(0,0,1);
			rotateAxis = Vector3D::crossMultiply(rotateAxis,normalEnd);
			
			glRotatef(
				RADIANS_TO_DEGREES(asin(rotateAxis.getMag())),
				GET_TRIPLET(rotateAxis)
			);
			
		}
    }glPopMatrix();
}

void tube(GLfloat radius, GLfloat segment_length) {
    glPolygonMode(GL_BACK, GL_LINE);
   // glPolygonMode(GL_FRONT, GL_LINE);
    
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
                    for (i = 360; i >= 0; i-=18) {
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

void drawCartesianAxis(){
	glPushMatrix(); 
    	glColor3f(RED);
		glBegin(GL_LINE_STRIP); 
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(10.0f, 0.0f, 0.0f);
		glEnd();
		
		glColor3f(GREEN);
		glBegin(GL_LINE_STRIP); 
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 10.0f, 0.0f);
		glEnd();
		
		glColor3f(BLUE);
		glBegin(GL_LINE_STRIP); 
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 10.0f);
		glEnd();
		
		//glutSolidTorus  ( 0.01f, 1.51f, 60, 60 );
	
		
		
	glPopMatrix();
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




void drawCircle(float radius, Vector3D axis, float centerOffset, Vector3D translationVector){
	
	
	int i;
	//glLoadIdentity();
	Vector3D centerVector = axis.getNormalizedVector()*centerOffset;
	Vector3D a = axis.getNormalizedVector().getUnitaryPerpendicularVector();
	Vector3D b = Vector3D::crossMultiply(axis.getNormalizedVector(),a).getNormalizedVector();
	/*
	int aa = a.getY()*axis.getZ() - a.getZ()*axis.getY();
	int bb = a.getZ()*axis.getX() - a.getX()*axis.getZ();
	int c = a.getX()*axis.getY() - a.getY()*axis.getX();
	printf("%f,%f,%f\n",aa, bb, c);				
	
	Vector3D b(aa,bb,c);
				
	printf("%f,%f,%f\n",a.getX(), a.getY(), a.getZ());				
	printf("%f,%f,%f\n",axis.getX(), axis.getY(), axis.getZ());				
	printf("%f,%f,%f\n",b.getX(), b.getY(), b.getZ());				
	*/						
				
	//printf("\n==========================\n");
	glPushMatrix(); 
    		//glTranslatef(centerVector.getX(), centerVector.getY(), centerVector.getZ());

		glColor3f(RED);
		
    		glBegin(GL_LINE_STRIP); 
			for (i = 360; i >= 0; i-=18) {
				GLfloat theta = i * PI/180;
				GLfloat x = centerVector.getX() + radius*cos(theta)*a.getX() + radius*sin(theta)*b.getX();
				GLfloat y = centerVector.getY() + radius*cos(theta)*a.getY() + radius*sin(theta)*b.getY();
				GLfloat z = centerVector.getZ() + radius*cos(theta)*a.getZ() + radius*sin(theta)*b.getZ();
				//printf("%f,%f,%f\n",x,y,z);				
				glVertex3f(x + translationVector.getX(), y + translationVector.getY(), z + translationVector.getZ());
			}
		glEnd();
		
		//glutSolidTorus  ( 0.01f, 1.51f, 60, 60 );
	
		
		
	glPopMatrix();
	//printf("\n==========================\n");
	
}

/************************************************************
	funcion para pintar el escenario
*************************************************************/
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glColor3f(1.0f,0.0f,0.0f);
	/*
	GLfloat angulo;
	int i; 
	glBegin(GL_LINE_STRIP);
	for (i=0; i<=360; i+=3)
	{
		  angulo = (GLfloat)i*3.14159f/180.0f; // grados a radianes
		  glVertex3f(cos(angulo), sin(angulo), 0.0f);
	}
	glEnd();
	*/
	//glLoadIdentity();	

	drawCartesianAxis();

	//xrot+=1.0f;
	//glRotatef(xrot,1.0f,0.0f, 0.0f);
		
	
	Vector3D aux1(1,2,3);
	Vector3D aux2(1,0.5,1);
	Vector3D aux3(-0.2,0,1);
	Vector3D aux4(-0.1,-0.1,1);
	
	customCylinder(
		1.0, 
		aux1, aux2,
		aux3, aux4,
		50
	);
	
	
	/*
	glColor3f(1.0f,0.0f,0.0f);
	Vector3D xAxis(1.0f,0.0f,0.0f);
	Vector3D yAxis(0.0f,1.0f,0.0f);
	Vector3D zAxis(0.0f,0.0f,1.0f);
	
	Vector3D origin(0.0f,0.0f,0.0f);
	//drawCircle(3.0f,xAxis,3.0f);
	//drawCircle(3.0f,yAxis,3.0f);
	//drawCircle(3.0f,zAxis,3.0f);
	float radius = 0.3f;
	float step = 0.07f;
	//gCAM_POS += xAxis*0.0005f;
	//gCAM_DIR.rotateYH( 1.0f*0.0005f );
	
	for(int i=0;i<180;i+=5){
		glRotatef(1.0f,0.0f, 0.1f, 0.0f);
		glTranslatef(step ,0.0f, 0.0f);
		drawCircle(radius,xAxis,0.0f,origin);
	
	}
	for(int i=0;i<180;i+=5){
		glRotatef(-1.0f,0.0f, 0.1f, 0.0f);
		glTranslatef(step ,0.0f, 0.0f);
		drawCircle(radius,xAxis,0.0f,origin);
	}
	for(int i=0;i<180;i+=5){
		glRotatef(-1.0f,0.0f, 0.0f, 1.0f);
		glTranslatef(step ,0.0f, 0.0f);
		drawCircle(radius,xAxis,0.0f,origin);
	}
	for(int i=0;i<180;i+=5){
		glRotatef(-1.0f,0.0f, 0.1f, 0.0f);
		glTranslatef(step ,0.0f, 0.0f);
		drawCircle(radius,xAxis,0.0f,origin);
	}
	for(int i=0;i<180;i+=5){
		glRotatef(1.0f,0.0f, 0.1f, 0.0f);
		glTranslatef(step ,0.0f, 0.0f);
		drawCircle(radius,xAxis,0.0f,origin);
	}
	for(int i=0;i<180;i+=5){
		glRotatef(-1.0f,0.0f, 0.0f, 1.0f);
		glTranslatef(step ,0.0f, 0.0f);
		drawCircle(radius,xAxis,0.0f,origin);
	}
*/
//	drawCircle(3.0f,zAxis,5.0f,xAxis);
		
	/*
	for(float i=0.0f;i<30.0f;i++){
		drawCircle(3.0f,zAxis,i,origin);
		origin.setX(zAxis.getX());
		origin.setY(zAxis.getY());
		origin.setZ(zAxis.getZ());
		zAxis.setX(zAxis.getX()*sin(6*PI/180));
		zAxis.setY(zAxis.getY()*sin(6*PI/180));
		zAxis.setZ(zAxis.getZ()*sin(6*PI/180));
	}*/
	//drawCartesianAxis();

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


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	



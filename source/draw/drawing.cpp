void customCylinder(PathSection section) {
	
    glPolygonMode(GL_BACK, GL_LINE);
    glPolygonMode(GL_FRONT, GL_LINE);//GL_FILL
    
	GLfloat x, y, z, theta;
	Vector3D centerVector, a, b;
	Vector3D posCenterIni = section.getPositionIni();
	Vector3D normalIni = section.getNormalIni();
	Vector3D posCenterEnd = section.getPositionEnd();
	Vector3D normalEnd = section.getNormalEnd();
	float radius = section.getRadius();
	int numSegment = section.getNumberOfSegments();
	
	if( normalIni.getX() == 0 and normalIni.getY() == 0 and normalIni.getZ() == 0 )
		normalIni.setZ(1);
	else
		normalIni.setNormalized();
	
	if( normalEnd.getX() == 0 and normalEnd.getY() == 0 and normalEnd.getZ() == 0 )
		normalEnd.setZ(1);
	else
		normalEnd.setNormalized();
	
	glTranslatef(GET_TRIPLET(posCenterIni));
		
	Vector3D rotateAxis(0,0,1);
	rotateAxis = Vector3D::crossMultiply(rotateAxis,normalIni);
	glRotatef(
		RADIANS_TO_DEGREES(asin(rotateAxis.getMag())),
		GET_TRIPLET(rotateAxis)
	);
	
	Vector3D aux;
	for(int j=0; j<numSegment; j++){
		glColor3f(BLUE);
		glBegin(GL_QUAD_STRIP);{
			for (int i = -36; i <= 216; i+=18) {
				theta = i * PI/180;
				x = radius * cos(theta);
				y = radius * sin(theta);
				z = 0;
				
				glVertex3f(x, y, z);
				
				aux = Vector3D(x,y,z);
				
				Vector3D rotateAxis(0,0,1);
				rotateAxis = Vector3D::crossMultiply(rotateAxis,normalEnd);
				
				aux = rotateVertex(aux,rotateAxis,RADIANS_TO_DEGREES(asin(rotateAxis.getMag())));
				aux = translateVertex(aux,posCenterEnd);
				
				glVertex3f(GET_TRIPLET(aux));	
			}
			int i = -36;
			theta = i * PI/180;
			x = radius * cos(theta);
			y = radius * sin(theta);
			z = 0;
			
			glVertex3f(x, y, z);
			
			aux = Vector3D(x,y,z);
			
			Vector3D rotateAxis(0,0,1);
			rotateAxis = Vector3D::crossMultiply(rotateAxis,normalEnd);
			
			aux = rotateVertex(aux,rotateAxis,RADIANS_TO_DEGREES(asin(rotateAxis.getMag())));
			aux = translateVertex(aux,posCenterEnd);
			
			glVertex3f(GET_TRIPLET(aux));	
			
		}glEnd();
		
		// Se pintan los objetos en la pista
		if(section.thereIsWhiteSphere(j))
			section.getWhiteSphere(j)->draw();
		
		if(section.thereIsBlueSphere(j))
			section.getBlueSphere(j)->draw();
			
		if(section.thereIsObstacle(j))
			section.getObstacle(j)->draw();
		
		
		glTranslatef(GET_TRIPLET(posCenterEnd));
		
		Vector3D rotateAxis(0,0,1);
		rotateAxis = Vector3D::crossMultiply(rotateAxis,normalEnd);
		glRotatef(
			RADIANS_TO_DEGREES(asin(rotateAxis.getMag())),
			GET_TRIPLET(rotateAxis)
		);
	}
}

void customCylinderTransformations(PathSection section){
    
	Vector3D centerVector, a, b;
	Vector3D posCenterIni = section.getPositionIni();
	Vector3D normalIni = section.getNormalIni()/* * -1*/;
	Vector3D posCenterEnd = section.getPositionEnd()/* * -1*/;
	Vector3D normalEnd = section.getNormalEnd()/* * -1*/;
	int numSegment = section.getNumberOfSegments();
	
	if( normalIni.getX() == 0 and normalIni.getY() == 0 and normalIni.getZ() == 0 )
		normalIni.setZ(1);
	else
		normalIni.setNormalized();
	
	if( normalEnd.getX() == 0 and normalEnd.getY() == 0 and normalEnd.getZ() == 0 )
		normalEnd.setZ(1);
	else
		normalEnd.setNormalized();
	
	Vector3D rotateAxis(0,0,1);
	rotateAxis = Vector3D::crossMultiply(rotateAxis,normalIni.getNormalizedVector());
	
	glTranslatef(GET_TRIPLET(posCenterIni));
	
	glRotatef(
		RADIANS_TO_DEGREES(asin(rotateAxis.getMag())),
		GET_TRIPLET(rotateAxis)
	);
	
	for(int j=0; j<numSegment; j++){
		
		
		Vector3D rotateAxis(0,0,1);
		rotateAxis = Vector3D::crossMultiply(rotateAxis,normalEnd.getNormalizedVector());
		
		glRotatef(
			RADIANS_TO_DEGREES(-asin(rotateAxis.getMag())),
			GET_TRIPLET(rotateAxis)
		);
		Vector3D aux = posCenterEnd * -1;
		glTranslatef(GET_TRIPLET(aux));
		
	}
}

void drawSolidCylinder(GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks){
	gluCylinder(quad, base, top, height, slices, stacks);
	glRotatef(180, 1,0,0);
	gluDisk(quad, 0.0f, base, slices, 1);
	glRotatef(180, 1,0,0);
	glTranslatef(0.0f, 0.0f, height);
	gluDisk(quad, 0.0f, top, slices, 1);
	glTranslatef(0.0f, 0.0f, -height);
}

void drawSolidPyramid( float r, float h){
	glBegin(GL_TRIANGLE_STRIP);{
		glVertex3f(    r, 0.0f,   -r );
		glVertex3f( 0.0f,    h, 0.0f );
		glVertex3f(   -r, 0.0f,   -r );
		glVertex3f(  -r , 0.0f,    r );
		glVertex3f(    r, 0.0f,   -r );
		glVertex3f(    r, 0.0f,    r );
		glVertex3f( 0.0f,    h, 0.0f );
		glVertex3f(  -r , 0.0f,    r );
	}glEnd();
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
	glPopMatrix();
}


void drawCar(){
	glColor3f(RED);
	glBegin(GL_QUAD_STRIP);{
		glVertex3f( CAR_WIDTH/2.0, CAR_WIDTH/3.0, CAR_LENGTH/2.0 );
		glVertex3f(-CAR_WIDTH/2.0, CAR_WIDTH/3.0, CAR_LENGTH/2.0 );
		glVertex3f( CAR_WIDTH/2.0,-CAR_WIDTH/3.0, CAR_LENGTH/2.0 );
		glVertex3f(-CAR_WIDTH/2.0,-CAR_WIDTH/3.0, CAR_LENGTH/2.0 );
		
		glVertex3f( CAR_WIDTH/2.0,-CAR_WIDTH/3.0,-CAR_LENGTH/2.0 );
		glVertex3f(-CAR_WIDTH/2.0,-CAR_WIDTH/3.0,-CAR_LENGTH/2.0 );
		glVertex3f( CAR_WIDTH/2.0, CAR_WIDTH/3.0,-CAR_LENGTH/2.0 );
		glVertex3f(-CAR_WIDTH/2.0, CAR_WIDTH/3.0,-CAR_LENGTH/2.0 );
		
		glVertex3f( CAR_WIDTH/2.0, CAR_WIDTH/3.0, CAR_LENGTH/2.0 );
		glVertex3f(-CAR_WIDTH/2.0, CAR_WIDTH/3.0, CAR_LENGTH/2.0 );
	}glEnd();
}

void drawPositionedCar(){
	
	gCAR_ROTATION = 90-RADIANS_TO_DEGREES(acos(gTUNNEL_PATH.getCurrentSection().getPositionEnd().getX()/0.05));
	
	if( fabs(gCAR_ROTATION-gCURRENT_CAR_ROTATION) >= 0.3 ){
		if( gCAR_ROTATION > gCURRENT_CAR_ROTATION ){
			gCURRENT_CAR_ROTATION += 0.3;
		}else if(gCAR_ROTATION < gCURRENT_CAR_ROTATION){
			gCURRENT_CAR_ROTATION -= 0.3;
		}
	}
	
	glPushMatrix();{
		glTranslatef( gCAR_POS.getX(), gCAR_POS.getY(), gCAR_POS.getZ()+CAR_LENGTH/2.0 );
			glRotatef( 
				gCURRENT_CAR_ROTATION, 
				0.0f,1.0f,0.0f 
			);
		glRotatef( gCAR_TILT, 0.0f,0.0f,1.0f );
		drawCar();
	}glPopMatrix();
}

void drawCarCollisionArea(){
	
	glColor3f(WHITE);
	
	glPushMatrix();{
		glTranslatef(gCAR_POS.getX(),gCAR_POS.getY(),gCAR_POS.getZ()+CAR_WIDTH/2.0);
		glutSolidCube(CAR_WIDTH);
	}glPopMatrix();
	
	glPushMatrix();{
		glTranslatef(gCAR_POS.getX(),gCAR_POS.getY(),gCAR_POS.getZ()+CAR_LENGTH-CAR_WIDTH/2.0);
		glutSolidCube(CAR_WIDTH);
	}glPopMatrix();
	
	glPushMatrix();{
		glTranslatef(gCAR_POS.getX(),gCAR_POS.getY(),gCAR_POS.getZ()+CAR_LENGTH/2.0);
		glutSolidCube(CAR_WIDTH);
	}glPopMatrix();
}


void drawCircle(float radius, Vector3D axis, float centerOffset, Vector3D translationVector){
	int i;
	Vector3D centerVector = axis.getNormalizedVector()*centerOffset;
	Vector3D a = axis.getNormalizedVector().getUnitaryPerpendicularVector();
	Vector3D b = Vector3D::crossMultiply(axis.getNormalizedVector(),a).getNormalizedVector();
	glPushMatrix(); 
    	
		glColor3f(RED);
		
    		glBegin(GL_LINE_STRIP); 
			for (i = 360; i >= 0; i-=18) {
				GLfloat theta = i * PI/180;
				GLfloat x = centerVector.getX() + radius*cos(theta)*a.getX() + radius*sin(theta)*b.getX();
				GLfloat y = centerVector.getY() + radius*cos(theta)*a.getY() + radius*sin(theta)*b.getY();
				GLfloat z = centerVector.getZ() + radius*cos(theta)*a.getZ() + radius*sin(theta)*b.getZ();
				glVertex3f(x + translationVector.getX(), y + translationVector.getY(), z + translationVector.getZ());
			}
		glEnd();
	glPopMatrix();
}

/************************************************************
	funcion para pintar el escenario
*************************************************************/

void drawScene() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int curveI;
	drawCartesianAxis();
	
	
	
	
	
		
	//glLightfv(GL_LIGHT0,GL_POSITION,pos);
    
	glPushMatrix();{
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	
	
		float scaleFactor = 0.01f;
		
		//glTranslatef(0.0f,gFLOAT_DEBUGy,gFLOAT_DEBUG);
		glTranslatef(0.0f,-0.05f,0.35f);
		glEnable(GL_RESCALE_NORMAL);
		
		glScalef(scaleFactor,scaleFactor,scaleFactor);
		
		glRotatef(180.0f,0.0f,1.0f,0.0f);
		
		//glTranslatef(0.0,-30.0,-100.0);
		
		GLfloat light_ambient[] = { 1.75, 1.75, 1.75, 1.0 };
		GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light_position[] = { 0.0, -10.0, -1.0, -0.5 };
		glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
		glLightfv (GL_LIGHT0, GL_POSITION, light_position);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glDepthFunc(GL_LESS);	
	
		
   
		glCallList(cube);	//draw the 3D mesh
		glDisable(GL_LIGHTING);
    
	}glPopMatrix();
	
	glPushMatrix();{
		gSEGMENT_PROGRESS -= gCAR_SPEED;
		gCAR_LAST_X = gCAR_POS.getX();
		if(gSEGMENT_PROGRESS <= -1.0f){//se termina la transformación del Model View para el segmento actual
			
			if(gTUNNEL_PATH.getCurrentUnusedSegments() > 1)						//queda algún segmento para consumir?
				gTUNNEL_PATH.consumeSegment();									//consumimos un segmento
			else{																//sino
				gTUNNEL_PATH.nextSection();
				//avanzamos a la siguiente sección (borrando el segmento actual)
				
				curveI = rand()%9;
				while( curveI==gPREV_INDEX[0] or curveI==gPREV_INDEX[1] or curveI==gPREV_INDEX[2] ){
					curveI = rand()%9;
				}
				gPREV_INDEX[0] = gPREV_INDEX[1];
				gPREV_INDEX[1] = gPREV_INDEX[2];
				gPREV_INDEX[2] = curveI;
				
				gCURVES[curveI].resetItems();
				gTUNNEL_PATH.pushSection(gCURVES[curveI]);		//volvemos a agregar el segmento actual a la cola
			}
			gSEGMENT_PROGRESS = 1 + gSEGMENT_PROGRESS;
		}
		
		Vector3D translation = gTUNNEL_PATH.getCurrentSection().getPositionEnd();
		Vector3D normal = gTUNNEL_PATH.getCurrentSection().getNormalEnd();
		Vector3D rotateAxis(0,0,1);
		rotateAxis = Vector3D::crossMultiply(rotateAxis,normal.getNormalizedVector());
	
		//se transforma el Model View para cada segmento consumido de la seccion actual		
		for(int i = 0; i < (gTUNNEL_PATH.getCurrentSection().getNumberOfSegments() - gTUNNEL_PATH.getCurrentUnusedSegments()) ; i++){
			glRotatef(
				RADIANS_TO_DEGREES(asin(rotateAxis.getMag()))*-1,
				GET_TRIPLET(rotateAxis)
			); 	
			glTranslatef(GET_TRIPLET((translation * -1)));
		}	
		
		//se transforma el Model View gradualmente para el segmento actual
		
		translation = translation * gSEGMENT_PROGRESS;
		
		glRotatef(
			RADIANS_TO_DEGREES(asin(rotateAxis.getMag()))*gSEGMENT_PROGRESS,
			GET_TRIPLET(rotateAxis)
		);
	
		glTranslatef(GET_TRIPLET(translation));

		for(int i = gTUNNEL_PATH.getIndex() - 1; i >= 0; i--){
			customCylinderTransformations(gTUNNEL_PATH.getSectionAt(i));
		}
		
		glPushMatrix();{
			for(int i = 0; i < gTUNNEL_PATH.getListSize(); i++){
				customCylinder(gTUNNEL_PATH.getSectionAt(i));
			}
		}glPopMatrix();
		
	}glPopMatrix();
	
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
void renderBitmapStringProjection( float x, float y, float z, const char* text ) {
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

void renderBitmapStringProjection( float x, float y, float z, const char* text, void *font ) {
	setOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(
		x,y,z,
		font,
		text
	);
	glPopMatrix();

	restorePerspectiveProjection();
}

string doubleToStr(double num);
void printGameData(){
	string stringToPrint;
	int shift = 0;
	int posX = gSCREEN.getW()-200;
	int posY = gSCREEN.getH()-25;
	
	stringToPrint = "Health ";
	int i;
	for( i=0; i<gCAR_HEALTH; i++ )
		stringToPrint += "[X]";
	for( i=i; i<3; i++ )
		stringToPrint += "[   ]";
	
	renderBitmapStringProjection( 
		posX, posY-shift, 0,
		stringToPrint.c_str()
	);
	
	shift += 22;
	
	stringToPrint = "Score  " + intToStr((double)gSCORE);
	renderBitmapStringProjection( 
		posX, posY-shift, 0,
		stringToPrint.c_str()
	);
	
	
	// /********************************************/
	// shift += 60;
	// renderBitmapStringProjection( gSCREEN.getW()-200, gSCREEN.getH()-25-shift, 0,	intToStr((double)gSCORE).c_str(),
		// GLUT_BITMAP_8_BY_13
	// );
	// stringToPrint = "Health: "; 
	// for( i=0; i<gCAR_HEALTH; i++ ) stringToPrint += "[X]";
	// for( i=i; i<3; i++ ) stringToPrint += "[_]";
	// renderBitmapStringProjection( gSCREEN.getW()-200, gSCREEN.getH()-25-20-shift, 0, stringToPrint.c_str(),
		// GLUT_BITMAP_8_BY_13
	// );
	
	// /********************************************/
	// shift += 60;
	// renderBitmapStringProjection( gSCREEN.getW()-200, gSCREEN.getH()-25-shift, 0,	intToStr((double)gSCORE).c_str(),
		// GLUT_BITMAP_9_BY_15
	// );
	// stringToPrint = "Health: "; 
	// for( i=0; i<gCAR_HEALTH; i++ ) stringToPrint += "[X]";
	// for( i=i; i<3; i++ ) stringToPrint += "[_]";
	// renderBitmapStringProjection( gSCREEN.getW()-200, gSCREEN.getH()-25-20-shift, 0, stringToPrint.c_str(),
		// GLUT_BITMAP_9_BY_15
	// );
	
	// /********************************************/
	// shift += 60;
	// renderBitmapStringProjection( gSCREEN.getW()-200, gSCREEN.getH()-25-shift, 0,	intToStr((double)gSCORE).c_str(),
		// GLUT_BITMAP_TIMES_ROMAN_10
	// );
	// stringToPrint = "Health: "; 
	// for( i=0; i<gCAR_HEALTH; i++ ) stringToPrint += "[X]";
	// for( i=i; i<3; i++ ) stringToPrint += "[_]";
	// renderBitmapStringProjection( gSCREEN.getW()-200, gSCREEN.getH()-25-20-shift, 0, stringToPrint.c_str(),
		// GLUT_BITMAP_TIMES_ROMAN_10
	// );
	
	// /********************************************/
	// shift += 60;
	// renderBitmapStringProjection( gSCREEN.getW()-200, gSCREEN.getH()-25-shift, 0,	intToStr((double)gSCORE).c_str(),
		// GLUT_BITMAP_TIMES_ROMAN_24
	// );
	// stringToPrint = "Health: "; 
	// for( i=0; i<gCAR_HEALTH; i++ ) stringToPrint += "[X]";
	// for( i=i; i<3; i++ ) stringToPrint += "[_]";
	// renderBitmapStringProjection( gSCREEN.getW()-200, gSCREEN.getH()-25-20-shift, 0, stringToPrint.c_str(),
		// GLUT_BITMAP_TIMES_ROMAN_24
	// );
	
	// /********************************************/
	// shift += 60;
	// renderBitmapStringProjection( gSCREEN.getW()-200, gSCREEN.getH()-25-shift, 0,	intToStr((double)gSCORE).c_str(),
		// GLUT_BITMAP_HELVETICA_10
	// );
	// stringToPrint = "Health: "; 
	// for( i=0; i<gCAR_HEALTH; i++ ) stringToPrint += "[X]";
	// for( i=i; i<3; i++ ) stringToPrint += "[_]";
	// renderBitmapStringProjection( gSCREEN.getW()-200, gSCREEN.getH()-25-20-shift, 0, stringToPrint.c_str(),
		// GLUT_BITMAP_HELVETICA_10
	// );
	
	// /********************************************/
	// shift += 60;
	// renderBitmapStringProjection( gSCREEN.getW()-200, gSCREEN.getH()-25-shift, 0,	intToStr((double)gSCORE).c_str(),
		// GLUT_BITMAP_HELVETICA_12
	// );
	// stringToPrint = "Health: "; 
	// for( i=0; i<gCAR_HEALTH; i++ ) stringToPrint += "[X]";
	// for( i=i; i<3; i++ ) stringToPrint += "[_]";
	// renderBitmapStringProjection( gSCREEN.getW()-200, gSCREEN.getH()-25-20-shift, 0, stringToPrint.c_str(),
		// GLUT_BITMAP_HELVETICA_12
	// );
	
	// /********************************************/
	// shift += 60;
	// renderBitmapStringProjection( gSCREEN.getW()-200, gSCREEN.getH()-25-shift, 0,	intToStr((double)gSCORE).c_str(),
		// GLUT_BITMAP_HELVETICA_18
	// );
	// stringToPrint = "Health: "; 
	// for( i=0; i<gCAR_HEALTH; i++ ) stringToPrint += "[X]";
	// for( i=i; i<3; i++ ) stringToPrint += "[_]";
	// renderBitmapStringProjection( gSCREEN.getW()-200, gSCREEN.getH()-25-20-shift, 0, stringToPrint.c_str(),
		// GLUT_BITMAP_HELVETICA_18
	// );
	
	
}	


/************************************************************
	funcion para imprimir datos internos relevantes del programa
*************************************************************/
void printVariables(){
	string stringToPrint;
	int shift = 15;
	
	stringToPrint = "Frame Rate: " + intToStr((int)gFPS) + " fps";
	renderBitmapStringProjection( 
		15, gSCREEN.getH()-shift, 0,
		stringToPrint.c_str()
	);
	shift += 25;
	
	stringToPrint = "gCAM_POS: " + gCAM_POS.toString();
	renderBitmapStringProjection( 
		15, gSCREEN.getH()-shift, 0,
		stringToPrint.c_str()
	);
	shift += 25;
	
	stringToPrint = "gCAM_DIR: " + gCAM_DIR.toString();
	renderBitmapStringProjection( 
		15, gSCREEN.getH()-shift, 0,
		stringToPrint.c_str()
	);
	shift += 25;
	
	stringToPrint = "gMOUSE: " + gMOUSE.toString();
	renderBitmapStringProjection( 
		15, gSCREEN.getH()-shift, 0,
		stringToPrint.c_str()
	);
	shift += 25;
	
	stringToPrint = "gDEBUG: " + gDEBUG;
	renderBitmapStringProjection( 
		15, gSCREEN.getH()-shift, 0,
		stringToPrint.c_str()
	);
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	



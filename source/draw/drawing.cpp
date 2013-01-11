void customCylinder(PathSection section) {
	
    glPolygonMode(GL_BACK, GL_LINE);
    glPolygonMode(GL_FRONT, GL_LINE);
    
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
		glColor3f(RED);
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
				// gDEBUG = rotateAxis.toString();
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
	
	//glLoadIdentity();
	glPushMatrix();{
		//glPolygonMode(GL_FRONT, GL_FILL);
		//glTranslatef(0.0f,1.5f,3.0f);
		float scaleFactor = 0.1f;
		glScalef(scaleFactor,scaleFactor,scaleFactor);
		glCallList(cube);	//draw the 3D mesh
	}glPopMatrix();
	
	glPushMatrix();{
	
		if(gSEGMENT_PROGRESS <= -1.0f){//se termina la transformación del Model View para el segmento actual
			
			if(gTUNNEL_PATH.getCurrentUnusedSegments() > 1)						//queda algún segmento para consumir?
				gTUNNEL_PATH.consumeSegment();									//consumimos un segmento
			else{																//sino
				gTUNNEL_PATH.nextSection();
				//avanzamos a la siguiente sección (borrando el segmento actual)
				curveI = rand()%9;
				while( curveI == 0 and gPREV_INDEX_ZERO ){ // verificacion para evitar dos caminos rectos (indice 0) consecutivos
					curveI = rand()%9;
				}

				if( curveI == 0 )
					gPREV_INDEX_ZERO = true;
				else
					gPREV_INDEX_ZERO = false;

				gTUNNEL_PATH.pushSection(gCURVES[curveI]);		//volvemos a agregar el segmento actual a la cola
			}
			gSEGMENT_PROGRESS = 0.0f;
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
			//DEBUG((gTUNNEL_PATH.getCurrentSection().getNumberOfSegments() - gTUNNEL_PATH.getCurrentUnusedSegments()));
		}	
		
		//se transforma el Model View gradualmente para el segmento actual
		gSEGMENT_PROGRESS -= gCAR_SPEED;
		
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


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	



void customCylinder(PathSection section) {
    
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
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	for(int j=0; j<numSegment; j++){
		glColor3f(BLUE);
		
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,gTUNNEL_TEXTURE[gCURRENT_TEXTURE_INDEX]);
		
		glPolygonMode(GL_BACK, GL_LINE);//GL_LINE
		glPolygonMode(GL_FRONT, GL_FILL);//GL_FILL
		
		glBegin(GL_QUAD_STRIP);{
			for (int i = -36; i <= 216; i+=18) {
				
				int a = (i/18.0 + 2);
				
				theta = i * PI/180;
				x = radius * cos(theta);
				y = radius * sin(theta);
				z = 0;
				glTexCoord2f(a>0?(1.0/14 * a):0,0);
				//glTexCoord2f(0,0);
				glVertex3f(x, y, z);
				
				//cout << "[" << x << "]" << "[" << y << "]"<< "[" << z << "]" << endl;
				
				aux = Vector3D(x,y,z);
				
				Vector3D rotateAxis(0,0,1);
				rotateAxis = Vector3D::crossMultiply(rotateAxis,normalEnd);
				
				aux = rotateVertex(aux,rotateAxis,RADIANS_TO_DEGREES(asin(rotateAxis.getMag())));
				aux = translateVertex(aux,posCenterEnd);
				
			//	glTexCoord2f(1.0/(i/18.0 + 2),1);
				//glTexCoord2f(1,1);
				glTexCoord2f(a>0?(1.0/14 * a):0,1);
				//glTexCoord2f(0,0);
				glVertex3f(GET_TRIPLET(aux));	
			}
		}glEnd();
		glBindTexture(GL_TEXTURE_2D,gTUNNEL_FLOOR_TEXTURE[gCURRENT_TEXTURE_INDEX]);
		glBegin(GL_QUAD_STRIP);{
			glTexCoord2f(0,0);
			glVertex3f(x, y, z);
			//cout << "[" << x << "]" << "[" << y << "]"<< "[" << z << "]" << endl << endl;
			int i = -36;
			theta = i * PI/180;
			x = radius * cos(theta);
			y = radius * sin(theta);
			z = 0;
			
			glTexCoord2f(0,1);
			glVertex3f(GET_TRIPLET(aux));	

			glTexCoord2f(1,0);
			glVertex3f(x, y, z);
			
			
			
			Vector3D aux2 = Vector3D(x,y,z);
			
			Vector3D rotateAxis(0,0,1);
			rotateAxis = Vector3D::crossMultiply(rotateAxis,normalEnd);
			
			aux2 = rotateVertex(aux2,rotateAxis,RADIANS_TO_DEGREES(asin(rotateAxis.getMag())));
			aux2 = translateVertex(aux2,posCenterEnd);
			
			
			glTexCoord2f(1,1);
			glVertex3f(GET_TRIPLET(aux2));	
			
			
		}glEnd();
		glPolygonMode(GL_BACK, GL_FILL);//GL_LINE
		glPolygonMode(GL_FRONT, GL_FILL);//GL_FILL
		glDisable(GL_TEXTURE_2D);
		
		// Se pintan los objetos en la pista
		
		
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);

		if(section.thereIsWhiteSphere(j))
			section.getWhiteSphere(j)->draw();
		
		if(section.thereIsBlueSphere(j))
			section.getBlueSphere(j)->draw();
			
		if(section.thereIsObstacle(j))
			section.getObstacle(j)->draw();
		
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	
		
		glTranslatef(GET_TRIPLET(posCenterEnd));
		
		Vector3D rotateAxis(0,0,1);
		rotateAxis = Vector3D::crossMultiply(rotateAxis,normalEnd);
		glRotatef(
			RADIANS_TO_DEGREES(asin(rotateAxis.getMag())),
			GET_TRIPLET(rotateAxis)
		);
		gCURRENT_TEXTURE_INDEX = gCURRENT_TEXTURE_INDEX + 1>= TEX_SEQ_QTY? 0 : gCURRENT_TEXTURE_INDEX + 1;  
		//cout << gCURRENT_TEXTURE_INDEX << endl;
	}
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
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

void drawWirePyramid( float r, float h){
	glPolygonMode(GL_BACK, GL_LINE);//GL_LINE
    glPolygonMode(GL_FRONT, GL_LINE);//GL_FILL
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
	glPolygonMode(GL_BACK, GL_FILL);//GL_LINE
    glPolygonMode(GL_FRONT, GL_FILL);//GL_FILL
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

	glPushMatrix();{
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	
		float scaleFactor = 0.00014f;
		
		//glTranslatef(0.0f,-0.25f,0.90f);
		
		GLfloat light_ambient[] = { 1.75, 1.75, 1.75, 1.0 };
		GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light_position[] = { 0.0, -10.0, -1.0, -0.5 };
		glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
		glLightfv (GL_LIGHT0, GL_POSITION, light_position);
			
		glEnable(GL_RESCALE_NORMAL);
		
		glScalef(scaleFactor,scaleFactor,scaleFactor);
		
		//glRotatef(180.0f,0.0f,1.0f,0.0f);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glDepthFunc(GL_LESS);	
	
		glCallList(gFIGHTER_MODEL);	//draw the 3D mesh
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_RESCALE_NORMAL);
    
	}glPopMatrix();
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
	
	if( gCAR_GHOST%2 == 0 ){
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
}

void drawCarCollisionArea(){
	
	glPolygonMode(GL_BACK, GL_LINE);//GL_LINE
    glPolygonMode(GL_FRONT, GL_LINE);//GL_FILL
	
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
	
	glPolygonMode(GL_BACK, GL_FILL);//GL_LINE
    glPolygonMode(GL_FRONT, GL_FILL);//GL_FILL
	
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
	if( gDEBUG_MODE ){
		drawCartesianAxis();
	}
	//dibujado del camino
	glPushMatrix();{
	
		//calculo de la posicion del path en relacion al punto 0,0,0
		
		gSEGMENT_PROGRESS -= gCAR_SPEED;
		gCAR_LAST_X = gCAR_POS.getX();
		if(gSEGMENT_PROGRESS <= -1.0f){//se termina la transformación del Model View para el segmento actual
			
			if(gTUNNEL_PATH.getCurrentUnusedSegments() > 1)						//queda algún segmento para consumir?
				gTUNNEL_PATH.consumeSegment();									//consumimos un segmento
			else{																//sino
				gTUNNEL_PATH.nextSection();										//avanzamos a la siguiente sección (borrando el segmento actual)
				
				curveI = rand()%9;
				while( curveI==gPREV_INDEX[0] or curveI==gPREV_INDEX[1] or curveI==gPREV_INDEX[2] ){
					curveI = rand()%9;
				}
				gPREV_INDEX[0] = gPREV_INDEX[1];
				gPREV_INDEX[1] = gPREV_INDEX[2];
				gPREV_INDEX[2] = curveI;
				
				gCURVES[curveI].resetItems();
				gTUNNEL_PATH.pushSection(gCURVES[curveI]);						//volvemos a agregar un segmento a la cola
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
		
		
		//dibujo efectivo
		glPushMatrix();{
			for(int i = 0; i < gTUNNEL_PATH.getListSize(); i++){
				customCylinder(gTUNNEL_PATH.getSectionAt(i));
			}
		}glPopMatrix();
		
	}glPopMatrix();
	
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
	
	// mover the origin from the bottom left corner
	// to the upper left corner
	glTranslatef(gSCREEN.getW()/2.0, gSCREEN.getH()/2.0, 0);
	
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


void printGameData(){
	stringstream ss;
	int shift = 0;
	int posX = gSCREEN.getW()/2-155;
	int posY = gSCREEN.getH()/2-40;
	
	ss << "Health: ";
	int i;
	for( i=0; i<gCAR_HEALTH; i++ )
		ss << "[X]";
	for( i=i; i<3; i++ )
		ss << "[   ]";
	
	renderBitmapStringProjection( 
		posX, posY+shift, 0,
		ss.str().c_str()
	);
	ss.str("");
	shift += 23;
	
	ss << "Score: " << gSCORE;
	renderBitmapStringProjection( 
		posX, posY+shift, 0,
		ss.str().c_str()
	);
	
	ss.str("");
	ss << "[ESC] Force Game Over";
	renderBitmapStringProjection( 
		-gSCREEN.getW()/2+20, -gSCREEN.getH()/2+30, 0,
		ss.str().c_str()
	);
	
}	


/************************************************************
	funcion para imprimir datos internos relevantes del programa
*************************************************************/
void printVariables(){
	string stringToPrint;
	int shift = 15;
	
	stringToPrint = "Frame Rate: " + intToStr((int)gFPS) + " fps";
	renderBitmapStringProjection( 
		-gSCREEN.getW()/2+15, gSCREEN.getH()/2-shift, 0,
		stringToPrint.c_str()
	);
	shift += 25;
	
	stringToPrint = "gCAM_POS: " + gCAM_POS.toString();
	renderBitmapStringProjection( 
		-gSCREEN.getW()/2+15, gSCREEN.getH()/2-shift, 0,
		stringToPrint.c_str()
	);
	shift += 25;
	
	stringToPrint = "gCAM_DIR: " + gCAM_DIR.toString();
	renderBitmapStringProjection( 
		-gSCREEN.getW()/2+15, gSCREEN.getH()/2-shift, 0,
		stringToPrint.c_str()
	);
	shift += 25;
	
	// stringToPrint = "gMOUSE: " + gMOUSE.toString();
	// renderBitmapStringProjection( 
		// 15, gSCREEN.getH()-shift, 0,
		// stringToPrint.c_str()
	// );
	// shift += 25;
	
	stringToPrint = "gDEBUG: " + gDEBUG;
	renderBitmapStringProjection( 
		-gSCREEN.getW()/2+15, gSCREEN.getH()/2-shift, 0,
		stringToPrint.c_str()
	);
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	



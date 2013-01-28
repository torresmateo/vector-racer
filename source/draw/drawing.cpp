//dibuja una sección del túnel
void customCylinder(PathSection section) {
    
    //variables de calculo de coordenadas y ángulos
	GLfloat x, y, z, theta;
    //posición del centro del túnel al inicio
	Vector3D posCenterIni = section.getPositionIni();
    //vector normal de la primera sección del túnel
	Vector3D normalIni = section.getNormalIni();
    //posición del centro del túnel al final
	Vector3D posCenterEnd = section.getPositionEnd();
    //vector normal de la sección final del túnel
	Vector3D normalEnd = section.getNormalEnd();
    //radio del túnel
	float radius = section.getRadius();
    //cantidad de segmentos de la sección
	int numSegment = section.getNumberOfSegments();
	
    //para evitar divisiones entre cero, verificamos que los vectores normales no apunten al origen (para que puedan ser normalizados)
	if( normalIni.getX() == 0 and normalIni.getY() == 0 and normalIni.getZ() == 0 )
		normalIni.setZ(1);
	else
		normalIni.setNormalized();
	
	if( normalEnd.getX() == 0 and normalEnd.getY() == 0 and normalEnd.getZ() == 0 )
		normalEnd.setZ(1);
	else
		normalEnd.setNormalized();
	
    //nos transladamos al origen del primer segmento
	glTranslatef(GET_TRIPLET(posCenterIni));
	
    //rotamos para mirar a donde apunta la normal inicial
	Vector3D rotateAxis(0,0,1);
	rotateAxis = Vector3D::crossMultiply(rotateAxis,normalIni);
	glRotatef(
		RADIANS_TO_DEGREES(asin(rotateAxis.getMag())),
		GET_TRIPLET(rotateAxis)
	);
	
    //vector auxiliar
	Vector3D aux;
	
    //habilitamos las luces
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
    //dibujamos todos los segmentos de esta sección
	for(int j=0; j<numSegment; j++){

        //seteamos el color (irrelevante en la versión final debido a las texturas)
		glColor3f(BLUE);
		
		//habilitamos el uso de texturas
		glEnable(GL_TEXTURE_2D);
        //hacemos el binding correspondiente
		glBindTexture(GL_TEXTURE_2D,gTUNNEL_TEXTURE[gCURRENT_TEXTURE_INDEX]);
		
        //seteamos el PolygonMode de tal forma a que el frente sea relleno y el fondo no
		glPolygonMode(GL_BACK, GL_LINE);//GL_LINE
		glPolygonMode(GL_FRONT, GL_FILL);//GL_FILL
		
        //dibujamos el techo del túnel
		glBegin(GL_QUAD_STRIP);{
            //iteramos sobre los grados del círculo
			for (int i = -36; i <= 216; i+=18) {
				//calculamos el porcentaje de textura que tenemos que asignar a cada punto
				int a = (i/18.0 + 2);
				
                //transformamos el ángulo a radianes
				theta = i * PI/180;

                //calculamos la coordenada de cada punto
				x = radius * cos(theta);
				y = radius * sin(theta);
				z = 0;
                //mapeamos la textura
				glTexCoord2f(a>0?(1.0/14 * a):0,0);
                //agregamos la coordenada
				glVertex3f(x, y, z);
				
                //calculamos la coordenada correspondiente en el final del segmento

                //utilizamos la coordenada que acabamos de agregar
				aux = Vector3D(x,y,z);
				
                
				Vector3D rotateAxis(0,0,1);
				rotateAxis = Vector3D::crossMultiply(rotateAxis,normalEnd);
				
                //rotamos y transladamos la coordenada para que se ubice en el final del segmento
				aux = rotateVertex(aux,rotateAxis,RADIANS_TO_DEGREES(asin(rotateAxis.getMag())));
				aux = translateVertex(aux,posCenterEnd);
				
                //mapeamos la textura
				glTexCoord2f(a>0?(1.0/14 * a):0,1);
                //agregamos la coordenada
				glVertex3f(GET_TRIPLET(aux));	
			}
		}glEnd();
        //dibujamos el suelo del túnel
        
        //hacemos el binding de textura correspondiente
		glBindTexture(GL_TEXTURE_2D,gTUNNEL_FLOOR_TEXTURE[gCURRENT_TEXTURE_INDEX]);
		glBegin(GL_QUAD_STRIP);{
            //mapeamos la textura
			glTexCoord2f(0,0);
            //agregamos la última coordenada (que se comparte con el techo de túnel)
			glVertex3f(x, y, z);

            
            //calculamos la coordenada con respecto al punto inicial
			int i = -36;
			theta = i * PI/180;
			x = radius * cos(theta);
			y = radius * sin(theta);
			z = 0;
			
            //mapeamos la textura
			glTexCoord2f(0,1);
            //agregamos la coordenada
			glVertex3f(GET_TRIPLET(aux));	

  
            //mapeamos la textura
			glTexCoord2f(1,0);
            //mapeamos la coordenada
			glVertex3f(x, y, z);
			
			//calculamos la última coordenada del suelo de forma similar a los demás puntos
            Vector3D aux2 = Vector3D(x,y,z);
			
			Vector3D rotateAxis(0,0,1);
			rotateAxis = Vector3D::crossMultiply(rotateAxis,normalEnd);
			
			aux2 = rotateVertex(aux2,rotateAxis,RADIANS_TO_DEGREES(asin(rotateAxis.getMag())));
			aux2 = translateVertex(aux2,posCenterEnd);
			
			//mapeamos la textura
			glTexCoord2f(1,1);
            //agregamos la coordenada
			glVertex3f(GET_TRIPLET(aux2));	
			
			
		}glEnd();

        //modificamos de nuevo el PolygonMode para que todas las figuras sean rellenas
		glPolygonMode(GL_BACK, GL_FILL);//GL_LINE
		glPolygonMode(GL_FRONT, GL_FILL);//GL_FILL

        //deshabilitamos el uso de texturas
		glDisable(GL_TEXTURE_2D);
		
		// Se pintan los objetos en la pista
		
        //deshabilitamos la iluminación
        glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		
		//si en esta sección tenemos una esfera blanca en el segmento actual dibujamos
		if(section.thereIsWhiteSphere(j))
			section.getWhiteSphere(j)->draw();
		
        //si en esta sección tenemos una esfera azul en el segmento actual dibujamos
		if(section.thereIsBlueSphere(j)){
            //la esfera azul tiene efectos de luz, por lo tanto habilitamos la iluminación
			glEnable(GL_LIGHTING);
		
            //configuramos otra fuente de luz especial para esta esfera
			GLfloat light_ambient[] = { 0.0, 0.0, 1.75, 1.0 };
			GLfloat light_diffuse[] = { 0.0, 1.0, 1.0, 1.0 };
			GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
			GLfloat light_position[] = { 0.0, -10.0, -1.0, 0.0 };
			glLightfv (GL_LIGHT2, GL_AMBIENT, light_ambient);
			glLightfv (GL_LIGHT2, GL_DIFFUSE, light_diffuse);
			glLightfv (GL_LIGHT2, GL_SPECULAR, light_specular);
			glLightfv (GL_LIGHT2, GL_POSITION, light_position);
			
            //habilitamos la luz recien configurada
			glEnable(GL_LIGHT2);

            //dibujamos la esfera
			section.getBlueSphere(j)->draw();

            //deshabilitamos la luz y la iluminación
			glDisable(GL_LIGHT2);
			glDisable(GL_LIGHTING);
		}	
        
        //si tenemos en esta sección un obstáculo en el segmento actual, lo dibujamos
		if(section.thereIsObstacle(j))
			section.getObstacle(j)->draw();
		
        //volvemos a habilitar la iluminación
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	
        //preparación para el dibujado del siguiente segmento

        //nos transladamos al final del segmento actual 
		glTranslatef(GET_TRIPLET(posCenterEnd));
		
        //rotamos para mirar a donde apunta la normal del final del segmento
		Vector3D rotateAxis(0,0,1);
		rotateAxis = Vector3D::crossMultiply(rotateAxis,normalEnd);
		glRotatef(
			RADIANS_TO_DEGREES(asin(rotateAxis.getMag())),
			GET_TRIPLET(rotateAxis)
		);

        //incrementamos el índice de las texturas del túnel de manera circular
		gCURRENT_TEXTURE_INDEX = gCURRENT_TEXTURE_INDEX + 1>= TEX_SEQ_QTY? 0 : gCURRENT_TEXTURE_INDEX + 1;  
	}

    //al terminar de dibujar deshabilitamos la iluminación
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}

//función que hace las transformaciones en sentido ivnerso, para mover el camino y que las secciones pasen siempre por el origen
void customCylinderTransformations(PathSection section){
    
    //esta función es muy similar a la función "customCylinder", la diferencia está 
    //en el orden de las transformaciones, que es exactamente inversa
	
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

//dibuja un cilindro sólido
void drawSolidCylinder(GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks){
	//dibuja un cilindro
    gluCylinder(quad, base, top, height, slices, stacks);
	//tapa
    glRotatef(180, 1,0,0);
	gluDisk(quad, 0.0f, base, slices, 1);
	//contratapa
    glRotatef(180, 1,0,0);
	glTranslatef(0.0f, 0.0f, height);
	gluDisk(quad, 0.0f, top, slices, 1);
	glTranslatef(0.0f, 0.0f, -height);
}

//dibuja una pirámide WireFrame
void drawWirePyramid( float r, float h){
    //seteamos el PolygonMode para lograr el WireFrame
	glPolygonMode(GL_BACK, GL_LINE);//GL_LINE
    glPolygonMode(GL_FRONT, GL_LINE);//GL_FILL

    //dibujamos la pirámide
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

    //reseteamos el PolygonMode de tal forma a que los dibujos sean rellenos
	glPolygonMode(GL_BACK, GL_FILL);//GL_LINE
    glPolygonMode(GL_FRONT, GL_FILL);//GL_FILL
}
	
//dibuja ejes cartesianos 
void drawCartesianAxis(){
    glPushMatrix(); 
    	//eje X en rojo
        glColor3f(RED);
		glBegin(GL_LINE_STRIP); 
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(10.0f, 0.0f, 0.0f);
		glEnd();
		
        //eje Y en verde
		glColor3f(GREEN);
		glBegin(GL_LINE_STRIP); 
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 10.0f, 0.0f);
		glEnd();
		
        //eje Z en azúl
		glColor3f(BLUE);
		glBegin(GL_LINE_STRIP); 
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 10.0f);
		glEnd();
	glPopMatrix();
}

//dibuja la nave
void drawCar(){

	glPushMatrix();{
        //seteamos el PolygonMode de tal forma que las figuras son rellenas
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	    
		
		//configuramos la luz adecuada para la nave
		GLfloat light_ambient[] = { 1.75, 1.75, 1.75, 1.0 };
		GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light_position[] = { 0.0, -10.0, -1.0, -0.5 };
		glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
		glLightfv (GL_LIGHT0, GL_POSITION, light_position);
	    
        //habilitamos el reescalamiento de normales (para no perder los efectos de luz)
		glEnable(GL_RESCALE_NORMAL);
		
        //escalamos el modelo de acorde al radio del túnel
		float scaleFactor = 0.00014f;
		glScalef(scaleFactor,scaleFactor,scaleFactor);
		
        //habilitamos la iluminación
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glDepthFunc(GL_LESS);	
	    
        //dibujamos el modelo
		glCallList(gFIGHTER_MODEL);

        //deshabilitamos la iluminación y el reecalamiento de normales
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_RESCALE_NORMAL);
    
	}glPopMatrix();
}

//transformaciones para el dibujado de la nave
void drawPositionedCar(){
	//calculamos la orientación de la nave con respecto al túnel
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
			//transladamos la nave a la posición correcta
            glTranslatef( gCAR_POS.getX(), gCAR_POS.getY(), gCAR_POS.getZ()+CAR_LENGTH/2.0 );
			
            //orientamos la nave en el sentido correcto
            glRotatef( 
				gCURRENT_CAR_ROTATION, 
				0.0f,1.0f,0.0f 
			);

            //inclinamiento de la nave
			glRotatef( gCAR_TILT, 0.0f,0.0f,1.0f );
			
            //dibujamos la nave
            drawCar();
		}glPopMatrix();
	}
}

//dibuja la caja de colisión de la nave
void drawCarCollisionArea(){
	
    //seteamos el PolygonMode en WireFrame
	glPolygonMode(GL_BACK, GL_LINE);//GL_LINE
    glPolygonMode(GL_FRONT, GL_LINE);//GL_FILL
	
    //dibujaremos una caja blanca
	glColor3f(WHITE);
	
    //dibujamos 3 cubos que representan la caja de colisión
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
	
    //seteamos el PolygonMode en relleno
	glPolygonMode(GL_BACK, GL_FILL);//GL_LINE
    glPolygonMode(GL_FRONT, GL_FILL);//GL_FILL
	
}

//dibuja un circulo
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
	//limpiamos el canvas
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    //indice de la curva
    int curveI;

    //si estamos en modo debug, dibujamos los ejes cartesianos
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
				
                //randomizamos la selección de la siguiente curva
				curveI = rand()%9;
                //no puede ser una curva recientemente utilizada
				while( curveI==gPREV_INDEX[0] or curveI==gPREV_INDEX[1] or curveI==gPREV_INDEX[2] ){
					curveI = rand()%9;
				}
                //shift circular del historial de curvas recientes
				gPREV_INDEX[0] = gPREV_INDEX[1];
				gPREV_INDEX[1] = gPREV_INDEX[2];
				gPREV_INDEX[2] = curveI;
				
                //preparamos la nueva curva con obstáculos
				gCURVES[curveI].resetItems();
                //agregamos la curva generada al stack de secciones de curva
				gTUNNEL_PATH.pushSection(gCURVES[curveI]);					
			}

            //avanzamos el offset del segmento
			gSEGMENT_PROGRESS = 1 + gSEGMENT_PROGRESS;
		}
		
        //calculamos el movimiento adecuado antes de dibujar efectivamente
        
        //inicialmente nos movemos lo que ya recorrimos del segmento actual
        
        //vector de translación
		Vector3D translation = gTUNNEL_PATH.getCurrentSection().getPositionEnd();
        //normal actual
		Vector3D normal = gTUNNEL_PATH.getCurrentSection().getNormalEnd();
		//ejede rotación
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
        
        //se transforma el Model View para cada sección consumida
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

	// Cambio a Projection Mode
	glMatrixMode(GL_PROJECTION);

    //Guardamos la matriz que contiene las configuraciones
    //para el modo en perspectiva
	glPushMatrix();

	// reseteanos la matriz
	glLoadIdentity();

	// seteamos un model view de proyección ortográfica
	gluOrtho2D(0, gSCREEN.getW(), gSCREEN.getH(), 0);
	
    // movemos el origen desde la esquina inferior izquierda
    // a la esquina superior izquierda
	glTranslatef(gSCREEN.getW()/2.0, gSCREEN.getH()/2.0, 0);
	
    //volvemos al ModelView Mode
	glMatrixMode(GL_MODELVIEW);
}


/************************************************************
	
*************************************************************/
void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restauramos la matriz de proytección previa
	glPopMatrix();

    //volvemos al ModelView Mode
	glMatrixMode(GL_MODELVIEW);
}

/************************************************************
	
*************************************************************/
void renderBitmapStringProjection( float x, float y, float z, const char* text ) {
    //entramos a modo ortho
	setOrthographicProjection();

	glPushMatrix();
    //reseteamos la matriz de transformación
	glLoadIdentity();
    //renderizamos el texto
	renderBitmapString(
		x,y,z,
		GLUT_BITMAP_HELVETICA_18,
		text
	);
	glPopMatrix();
    //volvemos a modo Perspectiva
	restorePerspectiveProjection();
}

void renderBitmapStringProjection( float x, float y, float z, const char* text, void *font ) {
    //entramos a modo Ortho
	setOrthographicProjection();

	glPushMatrix();
    //reseteamos la matriz de transformación
	glLoadIdentity();
    //dibujamos el texto
	renderBitmapString(
		x,y,z,
		font,
		text
	);
	glPopMatrix();
    //volvemos a modo Perspectiva
	restorePerspectiveProjection();
}

//imprime variables del jeugo en pantalla
void printGameData(){
    //buffer
	stringstream ss;
    //variables de posición
	int shift = 0;
	int posX = gSCREEN.getW()/2-155;
	int posY = gSCREEN.getH()/2-40;
	
    //imprimimios la vida restante
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
	
    //imprimimos el puntaje actual
	ss << "Score: " << gSCORE;
	renderBitmapStringProjection( 
		posX, posY+shift, 0,
		ss.str().c_str()
	);
    
	//imprimimos las instrucciones
	ss.str("");
	ss << "[ESC] RAGE QUIT";
	renderBitmapStringProjection( 
		-gSCREEN.getW()/2+20, -gSCREEN.getH()/2+30, 0,
		ss.str().c_str()
	);
	
}	


/************************************************************
funcion para imprimir datos internos relevantes del programa (modo debug)
*************************************************************/
void printVariables(){
	string stringToPrint;
	int shift = 15;
	//FPS
	stringToPrint = "Frame Rate: " + intToStr((int)gFPS) + " fps";
	renderBitmapStringProjection( 
		-gSCREEN.getW()/2+15, gSCREEN.getH()/2-shift, 0,
		stringToPrint.c_str()
	);
	shift += 25;
	//posición de la cámara
	stringToPrint = "gCAM_POS: " + gCAM_POS.toString();
	renderBitmapStringProjection( 
		-gSCREEN.getW()/2+15, gSCREEN.getH()/2-shift, 0,
		stringToPrint.c_str()
	);
	shift += 25;
	//dirección de la cámara
	stringToPrint = "gCAM_DIR: " + gCAM_DIR.toString();
	renderBitmapStringProjection( 
		-gSCREEN.getW()/2+15, gSCREEN.getH()/2-shift, 0,
		stringToPrint.c_str()
	);
	shift += 25;
	//string de debug global
	stringToPrint = "gDEBUG: " + gDEBUG;
	renderBitmapStringProjection( 
		-gSCREEN.getW()/2+15, gSCREEN.getH()/2-shift, 0,
		stringToPrint.c_str()
	);
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	



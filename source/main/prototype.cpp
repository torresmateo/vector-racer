//definiciones de funciones
// el objetivo es que esten diponibles en archivos previos al include

//calculo de frames por segundo
void calculateFPS();

//conversor de entero a string
string intToStr(int num);

//conversor de numeros con coma flotante a string
string doubleToStr(double num);

//dibujar la escena
void drawScene();

//dibujar una piramide WireFrame
void drawWirePyramid( float r, float h);

//cilindro solido
void drawSolidCylinder(GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks);

//dibujar una cadena en pantalla
void renderBitmapString( float, float, float, void *font, const char *text);

//dibujar una cadena con STROKE
void renderStrokeFontString(float, float, float, void *font, const char *text);
		
//utilizar la proyección en modo Ortho
void setOrthographicProjection();

//utilizar la proyección con perspectiva
void restorePerspectiveProjection();

//dibujar un string en pantalla con proyeccion
void renderBitmapStringProjection( float, float, float, const char* text );

//dibujar variables de debug
void printVariables();

//funcion principal de render
void display(void);

//callback de redimensión de la ventana
void changeSize(int newWidth, int newHigh);

//random customizado (mejor que el default =D )
float customRand( float limitDown, float limitUp, int decimal);

//manejador del estado post colisión de la nave
void carGhostHandler(int millisec);

//sumador de puntos
void scorePP(int millisec);

//resetea el estado de OpenGL a su configuración inicial de Materiales
void resetMaterials();





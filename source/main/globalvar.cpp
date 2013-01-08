

// position of the camera
Vector3D gCAM_POS(0.0f,0.0f,0.0f);
// actual vector representing the camera's direction
Vector3D gCAM_DIR(0.0f,0.0f,1.0f);
// punto a mirar por la camara
Vector3D gCAM_LOOK_AT(gCAM_POS+gCAM_DIR);
// velocidad de giro de la camara
double gCAM_ROTATE_SPEED = 0.01f;
// velocidad de translado de la camara
double gCAM_TRASNLATE_SPEED = 0.05f;

// Posicion del automovil
Vector3D gCAR_POS( gCAM_POS + gCAM_DIR*1.0f );
double gCAR_LATERAL_SHIFT = 0;

// width and height of the window
Vector2D gSCREEN; 



// ultima posicion del mouse
Vector2D gMOUSE(-1,-1); 




// default font
void *gFONT = GLUT_STROKE_ROMAN;



// variables to compute frames per second
int gFRAME = 0;
long gTIME;
long gTIMEBASE = 0;
double gFPS;
char gFPS_STRING[50];



// estructura para control de teclas presionadas
struct keysPressed {
	bool Q; //cambiar posicion del auto (izquierda)
	bool W; //avanzar en profundidad camara
	bool E; //cambiar posicion del auto (derecha)
	bool A; //movimiento lateral camara (izq)
	bool S; //retroceder en profuncidad camara
	bool D; //movimiento lateral de camara (derecha)
    bool Z; //shift vertical arriba (camara)
    bool C; //shift vertical abajo (camara)
	bool ESC; //salir
	// contador de teclas presionadas.
	// puede usarse como booleano para 
	// saber si alguna tecla esta presionada.
	int PRESSED;
} gKEY = {false,false,false,false,false,false,false,0};



// variable para impresion de debug
string gDEBUG;
GLfloat gFLOAT_DEBUG = 0;


//de Mateo BORRAR despues de las pruebas

GLfloat rtri;   //Angle for the Triangle (NEW)
GLfloat rquad;  //Rotation Angle for the Quad (new) 

bool light;
bool lp;
bool fp;

GLfloat xrot;
GLfloat yrot;
GLfloat xspeed;
GLfloat yspeed;
GLfloat z=-0.5f;

GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f }; 
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };  
GLuint  filter;                                 // Which Filter To Use
GLuint  texture[3];                             // Storage for 3 textures


























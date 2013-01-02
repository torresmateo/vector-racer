

// position of the camera
Vector3D gCAM_POS(0.0f,1.0f,5.0f);
// actual vector representing the camera's direction
Vector3D gCAM_DIR(0.0f,0.0f,1.0f);
// punto a mirar por la camara
Vector3D gCAM_LOOK_AT(gCAM_POS+gCAM_DIR);
// velocidad de giro de la camara
double gCAM_ROTATE_SPEED = 0.01f;
// velocidad de translado de la camara
double gCAM_TRASNLATE_SPEED = 0.08f;

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
	bool Q;
	bool W;
	bool E;
	bool A;
	bool S;
	bool D;
	bool ESC;
	// contador de teclas presionadas.
	// puede usarse como booleano para 
	// saber si alguna tecla esta presionada.
	int PRESSED;
} gKEY = {false,false,false,false,false,false,false,0};



// variable para impresion de debug
string gDEBUG;
































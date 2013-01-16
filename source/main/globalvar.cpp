

// position of the camera
Vector3D gCAM_POS(0.0f,0.0f,0.0f);
// actual vector representing the camera's direction
Vector3D gCAM_DIR(0.0f,0.0f,1.0f);
// punto a mirar por la camara
Vector3D gCAM_LOOK_AT(gCAM_POS+gCAM_DIR);
// velocidad de giro de la camara
double gCAM_ROTATE_SPEED = 0.01f;
// velocidad de translado de la camara
double gCAM_TRASNLATE_SPEED = 0.02f;

// Posicion del automovil
// Vector3D gCAR_POS( gCAM_POS + gCAM_DIR*1.0f );
// double gCAR_LATERAL_SHIFT = 0;

// width and height of the window
Vector2D gSCREEN; 

// ultima posicion del mouse
Vector2D gMOUSE(-1,-1); 

Vector3D gPATH_POS(0.0f,0.0f,0.0f);
Vector3D gPATH_NORMAL(0.0f,0.0f,1.0f);

// Curvas predefinidas
PathSection gCURVES[9];

// referentes al vehiculo
float gCAR_SPEED = 0.2f;
Vector3D gCAR_POS(0.0f,-0.25f,0.8f);
float gCAR_LAST_X = 0.0f;
float gCAR_LATERAL_SPEED = 0.025f;

// game
int gCAR_HEALTH = 3;
float gSCORE = 0;

float gSEGMENT_PROGRESS = 0.0f;

int gPREV_INDEX[3];

//modelview
GLfloat gMODEL_VIEW_MATRIX[16] = { 	1.0f, 0.0f, 0.0f, 0.0f,
                						0.0f, 1.0f, 0.0f, 0.0f,
                						0.0f, 0.0f, 1.0f, 0.0f,
                						0.0f, 0.0f, 0.0f, 1.0f };



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
    bool Z; //modifica la curva de forma vertical hacia arriba
    bool C; //modifica la curva de forma vertical hacia abajo
	bool ESC; //salir
	// contador de teclas presionadas.
	// puede usarse como booleano para 
	// saber si alguna tecla esta presionada.
	int PRESSED;
} gKEY = {false,false,false,false,false,false,false,0};


// variable para impresion de debug
string gDEBUG;
GLfloat gFLOAT_DEBUG = 0;
GLfloat gFLOAT_DEBUGy = 0;
GLfloat gFLOAT_DEBUGz = 0;

Path gTUNNEL_PATH;
PathSection gCURRENT_PATH_SECTION;




//de Mateo BORRAR despues de las pruebas

int cube;



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


























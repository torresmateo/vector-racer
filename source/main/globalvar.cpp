

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
float gCAR_TILT = 0.0f;
float gCAR_ROTATION = 0.0f;
float gCURRENT_CAR_ROTATION = 0.0f;

// game
int gCAR_HEALTH = 3;
int gCAR_GHOST = 0;
int gSCORE = 0;

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


Keyboard gKEYBOARD;

enum generalState { 
	MAIN_MENU,
	GAME_INIT,
	IN_GAME,
	EXIT
};

generalState gGENERAL_STATE = MAIN_MENU;

enum inGameState { 
	INSTRUCTIONS,
	PLAYING,
	GAME_OVER
};

inGameState gIN_GAME_STATE = INSTRUCTIONS;

// variable para impresion de debug
string gDEBUG;
GLfloat gFLOAT_DEBUG = 0;
GLfloat gFLOAT_DEBUGy = 0;
GLfloat gFLOAT_DEBUGz = 0;

Path gTUNNEL_PATH;
PathSection gCURRENT_PATH_SECTION;


int cube;//RENOMBRAR esta es la variable que carga el modelo del archivo .obj


























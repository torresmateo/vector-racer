

// posición de la camara
Vector3D gCAM_POS(0.0f,0.0f,0.0f);
// dirección de la camara
Vector3D gCAM_DIR(0.0f,0.0f,1.0f);
// punto a mirar por la camara
Vector3D gCAM_LOOK_AT(gCAM_POS+gCAM_DIR);
// velocidad de giro de la camara
double gCAM_ROTATE_SPEED = 0.01f;
// velocidad de translado de la camara
double gCAM_TRASNLATE_SPEED = 0.02f;


// tamaño de la ventana
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

float gSEGMENT_PROGRESS = 0.0f;//progreso de dibujado de un segmento

int gPREV_INDEX[3];//indice para el dibujado de segmentos

// fuente para el texto
void *gFONT = GLUT_STROKE_ROMAN;



// variables para computar los frames por segundo
int gFRAME = 0;
long gTIME;
long gTIMEBASE = 0;
double gFPS;
char gFPS_STRING[50];

Ranking gRANKING;

Keyboard gKEYBOARD;

//estados posibles del programa
enum generalState { 
	MAIN_MENU,
	IN_GAME,
	EXIT
};

//estado del programa
generalState gGENERAL_STATE = MAIN_MENU;

//estados posibles del juego 
enum inGameState { 
	INSTRUCTIONS,
	GAME_INIT,
	PLAYING,
	GAME_OVER_INIT,
	GAME_OVER,
	GAME_OVER_END
};

//estado del juego
inGameState gIN_GAME_STATE = INSTRUCTIONS;

//estados posibles del puntaje
enum scoreState {
	NONE,
	TOP_10,
	TOP
};

//estado del puntaje
scoreState gSCORE_STATE = NONE;

//nombre del jugador
string gPLAYER_NAME("");

//bandera de modo "debug"
bool gDEBUG_MODE = false;

// variables para impresion de debug
string gDEBUG;

//stack de secciones para el tunel
Path gTUNNEL_PATH;
//seccion actual del stack
PathSection gCURRENT_PATH_SECTION;

//variables de manejo de sonido
ISoundEngine* gSOUND_ENGINE = NULL;
ISound* gINGAME_MUSIC = NULL;
ISound* gMENU_MUSIC = NULL;
ISound* gGAMEOVER_SOUND = NULL;


bool gCONGRATS_DONE = false;

//cargador de modelos obj
objLoader gOBJ_LOADER;

 //index de la siguiente textura a pintar
int gCURRENT_TEXTURE_INDEX = 0;
//texturas para el tunel (paredes y techo)
unsigned int gTUNNEL_TEXTURE[TEX_SEQ_QTY];
//texturas para el tunel (piso)
unsigned int gTUNNEL_FLOOR_TEXTURE[TEX_SEQ_QTY];
//texturas del companion cube
unsigned int gCUBE_TEXTURE;
//textura de fondo para el menu principal
unsigned int gMAIN_MENU_BG;
//textura de fondo para la pantalla de instrucciones
unsigned int gINSTRUCTIONS_BG;
//textura de fondo para el diálogo de Game Over
unsigned int gGAME_OVER_BG;
//aountador al modelo de la nave
int gFIGHTER_MODEL;


























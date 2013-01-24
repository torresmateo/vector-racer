

void calculateFPS();

string intToStr(int num);

string doubleToStr(double num);



void drawScene();

void drawSnowMan();

void drawWirePyramid( float r, float h);

void drawSolidCylinder(GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks);

void renderBitmapString( float, float, float, void *font, const char *text);

void renderStrokeFontString(float, float, float, void *font, const char *text);
		
void setOrthographicProjection();

void restorePerspectiveProjection();

void renderBitmapStringProjection( float, float, float, const char* text );

void printVariables();

void display(void);

void changeSize(int newWidth, int newHigh);

float customRand( float limitDown, float limitUp, int decimal);

void carGhostHandler(int millisec);

void scorePP(int millisec);






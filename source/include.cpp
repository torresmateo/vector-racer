

// includes standar
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// includes propios de la aplicacion
#include "main/define.cpp"
#include "main/prototype.cpp"
#include "main/vector.cpp"
#include "main/matrix3.cpp"
#include "draw/pathSection.cpp"
#include "draw/path.cpp"
#include "main/globalvar.cpp"

#include "main/utils.cpp"

#include "input/keyboard.cpp"
#include "input/mouse.cpp"
#include "input/process.cpp"

#include "draw/drawing.cpp"
#include "draw/render.cpp"

#include "main/main.cpp"












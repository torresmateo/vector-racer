

/************************************************************
	matrices de transformación
*************************************************************/

Vector3D rotateVertex(Vector3D vertex, Vector3D axis, float degrees){
	float rad = degrees * (PI/180);	
	
	if(axis.getX()==0 and axis.getY()==0 and axis.getZ()==0 )
		return vertex;
		
	axis.setNormalized();
	
	float x = axis.getX();	
	float y = axis.getY();
	float z = axis.getZ();

	Matrix3 identity(1.0f,0.0f,0.0f,
					 0.0f,1.0f,0.0f,
					 0.0f,0.0f,1.0f);
	Matrix3 aaT = Matrix3(	x*x, x*y, x*z,
							x*y, y*y, y*z,
							x*z, y*z, z*z);

	Matrix3 aStar = Matrix3(	0.0f, -z		,  y		,
							z	, 0.0f	, -x		,
							-y	, x		, 0.0f	);
	Matrix3 aux1 = Matrix3::scalarMultiply(identity, cos(rad));
	//printf("(%f),%f,%f,%f\n\n",1-cos(rad),GET_TRIPLET(aux1.getRow1()));
	Matrix3 aux2 = Matrix3::scalarMultiply(aaT, (1-cos(rad)));
	Matrix3 aux3 = Matrix3::scalarMultiply(aStar, sin(rad));
	
	aux1+=aux2;
	aux1+=aux3;
	
	return aux1*=vertex;
}

Vector3D translateVertex(Vector3D vertex, Vector3D translationPoint){
	return vertex+=translationPoint;
}

/************************************************************
	calculo de frame rate
*************************************************************/
void calculateFPS() {
	gFRAME++;
	gTIME=glutGet(GLUT_ELAPSED_TIME);
	if (gTIME - gTIMEBASE > 1000) {
		gFPS = gFRAME*1000.0/(gTIME-gTIMEBASE);
		gTIMEBASE = gTIME;
		gFRAME = 0;
	}
}

void updateCameraLookAt(){
	// actualiza el punto a mirar 
	gCAM_LOOK_AT = gCAM_POS+gCAM_DIR;
	// posiciona vista
	gluLookAt(
		GET_TRIPLET(gCAM_POS),
		GET_TRIPLET(gCAM_LOOK_AT),
		0.0f, 1.0f,  0.0f
	);
}

void updateCameraLookAt( Vector3D position, Vector3D direction ){
	Vector3D camLookAt = position + direction;
	// posiciona vista
	gluLookAt(
		GET_TRIPLET(position),
		GET_TRIPLET(camLookAt),
		0.0f, 1.0f,  0.0f
	);
}

string intToStr(int num) {
   stringstream ss;
   ss << num;
   return ss.str();
}

string doubleToStr(double num) {
   stringstream ss;
   ss << num;
   return ss.str();
}


/************************************************************
	funciones que determinan la forma de la carretera
*************************************************************/

PathSection torusSection(float innerRadius, float outerRadius, unsigned int rings, float sectionAngleDeg, float orientationAngleDeg){
	//innerRadius: el radio de cada segmento
	//outerRadius: el radio del torus
	//rings: cuantos segmentos tiene esta sección
	//sectionAngleDeg que tantos grados del toro abarca
	//orientationAngleDeg hacia donde se curva el toro
	
	float segmentAngleDeg = sectionAngleDeg/rings; //ángulo abarcado por cada segmento
	float x = outerRadius * cos(orientationAngleDeg * (PI/180));
	float y = outerRadius * sin(orientationAngleDeg * (PI/180));
	Vector3D radiusVector(-x,-y,0);//negativo para poder usar el origen como punto de rotación
	Vector3D rotateAxis(0,0,1);
	rotateAxis = Vector3D::crossMultiply(rotateAxis,radiusVector);
	Vector3D rotatedRadius = rotateVertex(radiusVector,rotateAxis,segmentAngleDeg);
	Vector3D tanVector = rotateVertex(Vector3D(0,0,1),rotateAxis,segmentAngleDeg);
	PathSection torus;
	torus.setRadius(innerRadius);
	torus.setPositionEnd(radiusVector - rotatedRadius);
	torus.setNormalEnd(tanVector);
	torus.setNumberOfSegments(rings);
	return torus;

}


void loadPath(){

	int rings = 84;
	float sectionAngle = 60.160568f;
	float outerRadius = 40.0f;
	
	int ringsDownCase = 84;
	float sectionAngleDownCase = 24.064227;
	float outerRadiusDownCase = 100.0f;
	
	float torusOrientation = 0.0f;
	
	// PathSection seccion(torusSection(0.5f, 40.0f,rings, sectionAngle, 270.0f));
	// PathSection seccion2(torusSection(0.5f, 100.0f,ringsDownCase, sectionAngleDownCase, 90.0f));
	// PathSection seccion3(torusSection(0.5f, 40.0f,rings, sectionAngle, 270.0f));
	// PathSection seccion4(torusSection(0.5f, 80.0f,rings, sectionAngle, 90.0f));
	
	PathSection auxPath;
	auxPath.setRadius(0.5f);
	Vector3D auxPositionEnd(0.0f,0.0f,0.5f);
	auxPath.setPositionEnd(auxPositionEnd);
	auxPath.setNumberOfSegments(84);
	
	gCURVES[0] = auxPath;
	
	for(int i = 1; i<9; i++){
		if( 0 < torusOrientation and torusOrientation < 180 )
			gCURVES[i] = torusSection(0.5f, outerRadiusDownCase, ringsDownCase, sectionAngleDownCase, torusOrientation);
		else
			gCURVES[i] = torusSection(0.5f, outerRadius, rings, sectionAngle, torusOrientation);
		torusOrientation += 45;
	}
	
	gTUNNEL_PATH.pushSection(gCURVES[0]);
	gTUNNEL_PATH.pushSection(gCURVES[rand()%8 + 1]);
	gTUNNEL_PATH.pushSection(gCURVES[rand()%8 + 1]);
	
	
}

//OBJ LOADER

struct coordinate{
	float x,y,z;
	coordinate(float a,float b,float c) : x(a),y(b),z(c) {};
};

//for faces, it can contain triangles and quads as well, the four variable contain which is that
struct face{
	int facenum;
	bool four;
	int faces[4];
	face(int facen,int f1,int f2,int f3) : facenum(facen){	//constructor for triangle
		faces[0]=f1;
		faces[1]=f2;
		faces[2]=f3;
		four=false;
	}
	face(int facen,int f1,int f2,int f3,int f4) : facenum(facen){ //overloaded constructor for quad
		faces[0]=f1;
		faces[1]=f2;
		faces[2]=f3;
		faces[3]=f4;
		four=true;
	}
};

float angle=0.0;	//we rotate or object with angle degrees

int loadObject(const char* filename)
{
	std::vector<std::string*> coord;	//read every single line of the obj file as a string
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;	//normal vectors for every face
	std::ifstream in(filename);	//open the .obj file
	if(!in.is_open())	//if not opened, exit with -1
	{
		std::cout << "Nor oepened" << std::endl;
		return -1;
	}
	char buf[256];
	//read in every line to coord
	while(!in.eof())
	{
		in.getline(buf,256);
		coord.push_back(new std::string(buf));
	}
	//go through all of the elements of coord, and decide what kind of element is that
	for(int i=0;i<coord.size();i++)
	{
		if(coord[i]->c_str()[0]=='#')	//if it is a comment (the first character is #)
			continue;	//we don't care about that
		else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' ')	//if vector
		{
			float tmpx,tmpy,tmpz;
			sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);	//read in the 3 float coordinate to tmpx,tmpy,tmpz
			vertex.push_back(new coordinate(tmpx,tmpy,tmpz));	//and then add it to the end of our vertex list
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n')	//if normal vector
		{
			float tmpx,tmpy,tmpz;	//do the same thing
			sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			normals.push_back(new coordinate(tmpx,tmpy,tmpz));	
		}else if(coord[i]->c_str()[0]=='f')	//if face
		{
			int a,b,c,d,e;
			if(count(coord[i]->begin(),coord[i]->end(),' ')==3)	//if it is a triangle (it has 3 space in it)
			{
		  sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
				faces.push_back(new face(b,a,c,d));	//read in, and add to the end of the face list
			}else{
				sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
				faces.push_back(new face(b,a,c,d,e));	//do the same, except we call another constructor, and we use different pattern
			}
		}
	}
//raw
	int num;	//the id for the list
	num=glGenLists(1);	//generate a uniqe
	glNewList(num,GL_COMPILE);	//and create it
	for(int i=0;i<faces.size();i++)	
	{
		if(faces[i]->four)	//if it's a quad draw a quad
		{
			glBegin(GL_QUADS);
				//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
				//I subtract 1 because the index start from 0 in C++
				glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
				//draw the faces
				glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
				glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
				glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
				glVertex3f(vertex[faces[i]->faces[3]-1]->x,vertex[faces[i]->faces[3]-1]->y,vertex[faces[i]->faces[3]-1]->z);
			glEnd();
		}else{
			glBegin(GL_TRIANGLES);
				glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
				glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
				glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
				glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
			glEnd();
		}
	}
	glEndList();
	//delete everything to avoid memory leaks
	for(int i=0;i<coord.size();i++)
		delete coord[i];
	for(int i=0;i<faces.size();i++)
		delete faces[i];
	for(int i=0;i<normals.size();i++)
		delete normals[i];
	for(int i=0;i<vertex.size();i++)
		delete vertex[i];
	return num;	//return with the id
}

















































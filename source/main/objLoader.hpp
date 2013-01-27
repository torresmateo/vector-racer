//OBJ LOADER


#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP

//estructura para las coordenadas en 3 dimensiones
struct coordinate{
	float x,y,z;
	coordinate(float a,float b,float c) : x(a),y(b),z(c) {};
};

//para las caras, puede contener GL_QUADS y GL_TRIANGLES
struct face{
	//indice de la normal de la cara
	int faceNormal;
	//es un quad?
	bool four;
	//indice de los vectores que forman la cara (son 4 debido a la posibilidad de que sea quad)
	int faces[4];
	//indices de los vectores de mapping de textura
	int texCoord[4];
	//indice del stack de materiales asociado a esta cara
	int mat;
	//constructor para triángulos
	face(int facen,int f1,int f2,int f3, int t1, int t2, int t3, int m) : faceNormal(facen){	
		faces[0]=f1;
		faces[1]=f2;
		faces[2]=f3;
		texCoord[0] = t1;
		texCoord[1] = t2;
		texCoord[2] = t3;
		mat = m;
		four=false;
	}
	//constructor sobrecargado para quads
	face(int facen,int f1,int f2,int f3,int f4, int t1, int t2, int t3, int t4, int m) : faceNormal(facen){ 
		faces[0]=f1;
		faces[1]=f2;
		faces[2]=f3;
		faces[3]=f4;
		texCoord[0] = t1;
		texCoord[1] = t2;
		texCoord[2] = t3;
		texCoord[3] = t4;
		mat = m;
		four=true;
	}
};

//estructura para la definición de materiales
struct material{
	//nombre del material
	std::string name;
	//indices de transparencia, refraccion y shininess
	float alpha,ns,ni;
	//valores de reaccion a las luces
	float dif[3],amb[3],spec[3];
	//modelo de iluminacion
	int illum;
	//indice del stack de texturas
	int texture;
	//constructor
	material(const char* na, float alph, float n, float i, float * d, float * a, float * s, int il, int t){
		name		= na;
		alpha	= alph;
		ns		= n;
		ni		= i;
		
		dif[0]	= d[0];
		dif[1]	= d[1];
		dif[2]	= d[2];

		amb[0]	= a[0];
		amb[1]	= a[1];
		amb[2]	= a[2];
	
		spec[0]	= s[0];
		spec[1]	= s[1];
		spec[2]	= s[2];
		
		illum 	= il;
		texture	= t;
	};
};

//estructura para las coordenadas de texture mapping
struct textCoord{
	float u,v;
	textCoord(float a, float b){
		u = a;
		v = b;
	};
};

//definición de la clase
class objLoader{
	std::vector<std::string*> coord;		//cada linea del archivo .obj
	std::vector<coordinate*> vertex;		//cada vector
	std::vector<face*> faces;			//definicion de las caras de los poligonos
	std::vector<coordinate*> normals;		//vectores normales para cada face
	std::vector<unsigned int> texture;		//stack de texturas
	std::vector<unsigned int> lists;		//stack de modelos
	std::vector<material *> materials;		//stack de materiales
	std::vector<textCoord*> textureCoordinate;	//stack de coordenadas de mapping
	bool isMaterial,isNormals,isTexture;		//banderas de material, normales, y texturas
	
	unsigned int loadTexture(const char* fileName);	//loader de texturas (carga al stack)
	void clean();					//limpiador de la memoria
	
	public:
		objLoader();				//constructor
		~objLoader();				//destructor
		
		//cargador de textura utilitario (no afecta al stack)
		unsigned int loadSingleTexture(const char* fileName);
		//función de carga de modelos (parser)
		int load(const char* fileName);
	
};

#endif


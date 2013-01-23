//OBJ LOADER


#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP

struct coordinate{
	float x,y,z;
	coordinate(float a,float b,float c) : x(a),y(b),z(c) {};
};

//for faces, it can contain triangles and quads as well, the four variable contain which is that
struct face{
	int faceNormal;
	bool four;
	int faces[4];
	int texCoord[4];
	int mat;
	face(int facen,int f1,int f2,int f3, int t1, int t2, int t3, int m) : faceNormal(facen){	//constructor for triangle
		faces[0]=f1;
		faces[1]=f2;
		faces[2]=f3;
		texCoord[0] = t1;
		texCoord[1] = t2;
		texCoord[2] = t3;
		mat = m;
		four=false;
	}
	face(int facen,int f1,int f2,int f3,int f4, int t1, int t2, int t3, int t4, int m) : faceNormal(facen){ //overloaded constructor for quad
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

struct material{
	std::string name;
	float alpha,ns,ni;
	float dif[3],amb[3],spec[3];
	int illum;
	int texture;
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

struct textCoord{
	float u,v;
	textCoord(float a, float b){
		u = a;
		v = b;
	};
};

class objLoader{
	std::vector<std::string*> coord;	//cada linea del archivo .obj
	std::vector<coordinate*> vertex;	//cada vector
	std::vector<face*> faces;			//definicion de las caras de los poligonos
	std::vector<coordinate*> normals;	//vectores normales para cada face
	std::vector<unsigned int> texture;
	std::vector<unsigned int> lists;
	std::vector<material *> materials;
	std::vector<textCoord*> textureCoordinate;
	bool isMaterial,isNormals,isTexture;
	
	unsigned int loadTexture(const char* fileName);
	void clean();
	
	public:
		objLoader();
		~objLoader();
		
		int load(const char* fileName);
	
};

#endif


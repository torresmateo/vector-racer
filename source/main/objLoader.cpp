
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
	int texCoord[4];
	int mat;
	face(int facen,int f1,int f2,int f3, int t1, int t2, int t3, int m) : facenum(facen){	//constructor for triangle
		faces[0]=f1;
		faces[1]=f2;
		faces[2]=f3;
		texCoord[0] = t1;
		texCoord[1] = t2;
		texCoord[2] = t3;
		mat = m;
		four=false;
	}
	face(int facen,int f1,int f2,int f3,int f4, int t1, int t2, int t3, int t4, int m) : facenum(facen){ //overloaded constructor for quad
		faces[0]=f1;
		faces[1]=f2;
		faces[2]=f3;
		faces[3]=f4;
		texCoord[0] = t1;
		texCoord[1] = t2;
		texCoord[2] = t3;
		texCoord[2] = t4;
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
	std::vector<std::string*> coord;	//read every single line of the obj file as a string
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;	//normal vectors for every face
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


int objLoader::load(const char* filename)
{
	std::ifstream in(filename);	//open the .obj file
	if(!in.is_open())	//if not opened, exit with -1
	{
		std::cout << "Nor oepened" << std::endl;
		return -1;
	}
	char buf[256];
	int curMat = 0;
	//read in every line to coord
	while(!in.eof())
	{
		in.getline(buf,256);
		coord.push_back(new std::string(buf));
	}
	//go through all of the elements of coord, and decide what kind of element is that
	for(unsigned int i=0;i<coord.size();i++)	{
		if(coord[i]->c_str()[0]=='#')
			continue;
		else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' '){
			float tmpx,tmpy,tmpz;
			sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);
			vertex.push_back(new coordinate(tmpx,tmpy,tmpz));
		}else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n'){
			float tmpx,tmpy,tmpz;
			sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			normals.push_back(new coordinate(tmpx,tmpy,tmpz));	
		}else if(coord[i]->c_str()[0]=='f'){	
			int a,b,c,d,e;
			if(count(coord[i]->begin(),coord[i]->end(),' ')==3){
				if(coord[i]->find("//") != std::string::npos){
					int t[3];
					sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
					faces.push_back(new face(b,a,c,d,t[0],t[1],t[2],curMat));
				}else if(coord[i]->find("/") != std::string::npos){
					int t[3];
					sscanf(coord[i]->c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d",&a,&t[0],&b,&c,&t[1],&b,&d,&t[2],&b);
					faces.push_back(new face(b,a,c,d,t[0],t[1],t[2],curMat));	
				}else{
					sscanf(coord[i]->c_str(),"f %d %d %d",&a,&b,&c);
					faces.push_back(new face(-1,a,b,c,0,0,0,curMat));
				}
			}else{
				if(coord[i]->find("//") != std::string::npos){
					sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
					faces.push_back(new face(b,a,c,d,e,0,0,0,0,curMat));
				}else if(coord[i]->find("/") != std::string::npos){
					int t[4];
					sscanf(coord[i]->c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",&a,&t[0],&b,&c,&t[1],&b,&d,&t[2],&b,&e,&t[3],&b);
					faces.push_back(new face(b,a,c,d,e,t[0],t[1],t[2],t[3],curMat));	
				}else{
					sscanf(coord[i]->c_str(),"f %d %d %d %d",&a,&b,&c,&d);
					faces.push_back(new face(-1,a,b,c,d,0,0,0,0,curMat));
				}
			}
		}else if(coord[i]->c_str()[0] == 'u' && coord[i]->c_str()[1] == 's' && coord[i]->c_str()[2] == 'e'){
			char tmp[200];
			sscanf(coord[i]->c_str(),"usemtl %s",tmp);
			for(unsigned int i = 0 ; i < materials.size(); i++){
				if(strcmp(materials[i]->name.c_str(),tmp)==0){
					curMat = i;
					break;
				}
			}
		}else if(coord[i]->c_str()[0] == 'm' && coord[i]->c_str()[1] == 't' && coord[i]->c_str()[2] == 'l' && coord[i]->c_str()[3] == 'l'){
			char fileN[200];
			sscanf(coord[i]->c_str(),"mtllib %s",fileN);
			std::ifstream mtlin(fileN);
			if(!mtlin.is_open()){
				std::cout << "Can not open the material file" << std::endl;
				clean();
				return -1;
			}
			isMaterial = true;
			std::vector<std::string> tmp;
			char buf[200];
			while(!mtlin.eof()){
				mtlin.getline(buf,200);
				tmp.push_back(buf);
			}
			char name[200];
			char filename[200];
			float amb[3],dif[3],spec[3], alpha, ns, ni;
			int illum;
			unsigned int texture;
			bool isMaterial = false;
			strcpy(filename,"\0");
			for(unsigned int i=0; i < tmp.size(); i++){
				if(tmp[i][0] == '#')
					continue;
				if(tmp[i][0] == 'n' && tmp[i][1] == 'e' && tmp[i][2] == 'w'){
					if(isMaterial){
						if(strcmp(filename,"\0") != 0){
							materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, texture));
							strcpy(filename,"\0");
						}else{
							materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, -1));
						}
					}
					isMaterial = false;
					sscanf(tmp[i].c_str(),"newmtl %s",name);
				}else if(tmp[i][0] == 'N' && tmp[i][1] == 's'){
					sscanf(tmp[i].c_str(),"Ns %f",&ns);
					isMaterial = true;
				}else if(tmp[i][0] == 'K' && tmp[i][1] == 'a'){
					sscanf(tmp[i].c_str(),"Ka %f %f %f",&amb[0],&amb[1],&amb[2]);
					isMaterial = true;
				}else if(tmp[i][0] == 'K' && tmp[i][1] == 'd'){
					sscanf(tmp[i].c_str(),"Ka %f %f %f",&dif[0],&dif[1],&dif[2]);
					isMaterial = true;
				}else if(tmp[i][0] == 'K' && tmp[i][1] == 's'){
					sscanf(tmp[i].c_str(),"Ka %f %f %f",&spec[0],&spec[1],&spec[2]);
					isMaterial = true;
				}else if(tmp[i][0] == 'N' && tmp[i][1] == 'i'){
					sscanf(tmp[i].c_str(),"Ni %f",&ni);
					isMaterial = true;
				}else if(tmp[i][0] == 'd' && tmp[i][1] == ' '){
					sscanf(tmp[i].c_str(),"d %f",&alpha);
					isMaterial = true;
				}else if(tmp[i][0] == 'i' && tmp[i][1] == 'l'){
					sscanf(tmp[i].c_str(),"illum %d",&illum);
					isMaterial = true;
				}else if(tmp[i][0] == 'm' && tmp[i][1] == 'a'){
					sscanf(tmp[i].c_str(),"map_Kd %s",filename);
					texture = loadTexture(filename);
					isMaterial = true;
				}
				
			}
			if(isMaterial){
				if(strcmp(filename,"\0") != 0){
					materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, texture));
				}else{
					materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, -1));
				}
			}else if(coord[i]->c_str()[0] == 'v' && coord[i]->c_str()[1] == 't'){
				float u,v;
				sscanf(coord[i]->c_str(),"vt %f %f",&u,&v);
				textureCoordinate.push_back(new textCoord(u,1-v));
				isTexture = true;
			}
			if(materials.size() == 0)
				isMaterial = false;
			else
				isMaterial = true;
			
		}
	}
//raw
	int num;
	num=glGenLists(1);
	glNewList(num,GL_COMPILE);
	int last = -1;
	for(unsigned int i=0;i<faces.size();i++)	{
		if(last != faces[i]->mat && isMaterial){
			float diffuse[]={materials[faces[i]->mat]->dif[0],materials[faces[i]->mat]->dif[1],materials[faces[i]->mat]->dif[2],1.0};
			float ambient[]={materials[faces[i]->mat]->amb[0],materials[faces[i]->mat]->amb[1],materials[faces[i]->mat]->amb[2],1.0};
			float specular[]={materials[faces[i]->mat]->spec[0],materials[faces[i]->mat]->spec[1],materials[faces[i]->mat]->spec[2],1.0};
			glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
			glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
			glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
			glMaterialf(GL_FRONT,GL_SHININESS,materials[faces[i]->mat]->ns);
			last=faces[i]->mat;
			if(materials[faces[i]->mat]->texture == -1){
				glDisable(GL_TEXTURE_2D);
			}else{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,materials[faces[i]->mat]->texture);
			}
			
		}
		if(faces[i]->four){
			glBegin(GL_QUADS);
				glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
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
	clean();
	lists.push_back(num);
	return num;	//return with the id
}

void objLoader::clean(){
	for(unsigned int i=0;i<coord.size();i++)
		delete coord[i];
	for(unsigned int i=0;i<faces.size();i++)
		delete faces[i];
	for(unsigned int i=0;i<normals.size();i++)
		delete normals[i];
	for(unsigned int i=0;i<vertex.size();i++)
		delete vertex[i];
	for(unsigned int i=0;i<materials.size();i++)
		delete materials[i];
	for(unsigned int i=0;i<textureCoordinate.size();i++)
		delete textureCoordinate[i];
	coord.clear();
	faces.clear();
	normals.clear();
	vertex.clear();
	materials.clear();
	textureCoordinate.clear();
}

objLoader::objLoader(){
	isMaterial = false;
	isNormals = false;
	isTexture = false;
}

objLoader::~objLoader(){
	for(std::vector<unsigned int>::const_iterator it=texture.begin(); it!=texture.end(); it++){
		glDeleteTextures(1,&(*it));
	}
	for(std::vector<unsigned int>::const_iterator it=lists.begin(); it!=lists.end(); it++){
		glDeleteLists(*it,1);
	}
}

unsigned int objLoader::loadTexture(const char * filename){
	unsigned int num;
	glGenTextures(1,&num);
	Image* img = loadBMP("vtr.bmp");
	
	//loadBMP
	glBindTexture(GL_TEXTURE_2D,num);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	delete img;
	texture.push_back(num);
	return num;
}




























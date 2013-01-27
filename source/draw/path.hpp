#ifndef PATH_H
#define PATH_H

//Clase que permite el manejo en forma de cola de las secciones del túnel
class Path {
	//lista de secciones
	vector<PathSection> sectionList;
    //sección actual
	PathSection currentSection;
    //indice actual del stack
	unsigned int index;
    //segmentos sin usar en la sección actual
	int currentUnusedSegments;
	public:
	
		//constructors
		
		Path() {}
		
		Path(vector<PathSection> sectionList) {
			for(unsigned int i ; i < sectionList.size(); i++){
				this->pushSection(sectionList[i]);
			}
		}
		
		//seters
		//geters
		PathSection getCurrentSection(){
			return currentSection;
		}
		
		PathSection getNextSection(){
			return sectionList[index + 1];
		}
		
		PathSection getSectionAt(unsigned int index){
			if(sectionList.size() > index)
				return sectionList[index];
			return sectionList[0];
		}
		
		int getCurrentUnusedSegments(){
			return currentUnusedSegments;
		}
		
		int getCurrentSegmentsIndex(){
			return currentSection.getNumberOfSegments() - currentUnusedSegments;
		}
		
		unsigned int getIndex(){
			return index;
		}
		
		int getSegmentQty(){
			int totalQty = 0;
			for(unsigned int i; i < sectionList.size(); i++){
				totalQty += sectionList[i].getNumberOfSegments();
			}
			return totalQty;
		}
		
		int getListSize(){
			return sectionList.size();
		}
		//utils
        
        //agrega una sección al final del stack
		void pushSection(PathSection section){
			sectionList.push_back(section);
            //si es el primer elemento, seteamos las variables internas acordemente
			if(sectionList.size() == 1){
				this->currentSection = sectionList[0];
				this->currentUnusedSegments = sectionList[0].getNumberOfSegments();
				index = 0;
			}
		}
		
        //avanza a la siguiente sección del stack
		void nextSection(){//circularidad
            //eliminamos la sección inicial del stack
			sectionList.erase(sectionList.begin());
            //restamos el índice de la sección actual
			index--;
			if(index >= sectionList.size()){
				index = 0;
			}else{
				index++;
			}
            //actualizamos las variables internas
			currentSection = sectionList[index];
			currentUnusedSegments = currentSection.getNumberOfSegments();
		}

		//consumir un segmento de la sección actual
		void consumeSegment(){
			currentUnusedSegments--;
		}
		
};
#endif

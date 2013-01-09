#ifndef PATH_H
#define PATH_H
#include <vector>
class Path {
	
	vector<PathSection> sectionList;
	PathSection currentSection;
	unsigned int index;
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
		
		PathSection getSectionAt(unsigned int index){
			if(sectionList.size() > index)
				return sectionList[index];
			return sectionList[0];
		}
		
		int getCurrentUnusedSegments(){
			return currentUnusedSegments;
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
		void pushSection(PathSection section){
			sectionList.push_back(section);
			if(sectionList.size() == 1){
				this->currentSection = sectionList[0];
				this->currentUnusedSegments = sectionList[0].getNumberOfSegments();
				index = 0;
			}
		}
		
		void nextSection(){//circularidad
			if(index >= sectionList.size()){
				index = 0;
			}else{
				index++;
			}
			currentSection = sectionList[index];
			currentUnusedSegments = currentSection.getNumberOfSegments();
		}
		
		void consumeSegment(){
			currentUnusedSegments--;
		}
		
};
#endif

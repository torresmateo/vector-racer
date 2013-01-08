#ifndef PATH_H
#define PATH_H
class Path {
	
	Path *nextStep;
	PathSection sectionInfo;
	public:
	
		//constructors
		
		Path() {
			this->sectionInfo = PathSection();
			nextStep = NULL;
		}
		
		Path( PathSection sectionInfo, Path * nextStep ) {
			this->sectionInfo = sectionInfo;
			nextStep = nextStep;
		}
		
		//seters
		//geters
		//utils
};
#endif

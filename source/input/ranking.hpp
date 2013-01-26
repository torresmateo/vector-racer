

#include <utility>

class Ranking {
	
	set< pair<int,string> > playersList;
	
	public:
		
		Ranking(){
			retrieveData();
			setData();
		}
	
		void insert( string playerName, int score );
		
		void retrieveData();
		void setData();
		void clear();
		
		bool isHighestScore( int score );
		bool isTop10( int score );
		void draw();
		
};




#include <utility>

// clase utilizada para manejar el top 10
class Ranking {
	
	// conjunto de pares <puntaje,jugador>
	set< pair<int,string> > playersList;
	
	public:
		// el constructor lee el archivo, lo reformatea y lo escribe nuevamente.
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


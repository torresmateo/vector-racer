
#include "ranking.hpp"

// inserta un nuevo par <puntaje,jugador>
// el set ordena los elementos automaticamente
// el onceavo par (el que cae fuera del top10) se elimina
void Ranking::insert( string playerName, int score ){
	playersList.insert( std::pair<int,string>(score,playerName) );
	for (
		set< pair<int,string> >::iterator it=playersList.begin(); 
		playersList.size()>10;
		++it
	){ playersList.erase(it); }
}

// extre los datos del archivo de ranking y los asigna a la propiedad "playersList" del objeto
void Ranking::retrieveData(){
	playersList.clear();
	fstream rankingFile("ranking (do not modify).txt");
	
	char lineBuffer0[256] = {0};
	char lineBuffer1[256] = {0};
	
	rankingFile.getline(lineBuffer0,256);
	while( rankingFile.good() and string(lineBuffer0)!="" ){
		rankingFile.getline(lineBuffer1,256);
		if( !rankingFile.good() or string(lineBuffer1)=="" ){
			rankingFile.close();
			return;
		}
		this->insert(lineBuffer0,atoi(lineBuffer1));
		rankingFile.getline(lineBuffer0,256);
	}
	
	rankingFile.close();
}

// actualiza el archivo con los nuevos datos
void Ranking::setData(){
	fstream rankingFile("ranking (do not modify).txt",ios_base::in|ios_base::out|ios_base::trunc);
	
	for (
		set< pair<int,string> >::reverse_iterator rit=playersList.rbegin(); 
		rit != playersList.rend(); 
		++rit
	){ rankingFile << rit->second << '\n' << rit->first << '\n'; }
	
	rankingFile.close();
}

// vacia la lista de puntajes
void Ranking::clear(){
	playersList.clear();
}

// se utiliza para saber si un puntaje dado es el mas alto con respecto a los puntajes actuales en el objeto
bool Ranking::isHighestScore( int score ){
	if( playersList.size() == 0 )
		return true;
		
	if( score > playersList.rbegin()->first )
		return true;
	
	return false;
}

// se utiliza para saber si un puntaje dado esta en el top 10 con respecto a los puntajes actuales en el objeto
bool Ranking::isTop10( int score ){
	if( playersList.size() < 10 )
		return true;
	
	if( score > playersList.begin()->first )
		return true;
	
	return false;
}

// dibuja los puntajes en pantalla
void Ranking::draw(){
	stringstream ss;
	int shifty = -40;
	int shiftx = 258;
	
	// preparacion para impresion en pantalla
	setOrthographicProjection();
		glPushMatrix();
			glLoadIdentity();
			glColor3f(CYAN);
			
			int i=1;
			for (
				set< pair<int,string> >::reverse_iterator rit=playersList.rbegin(); 
				rit != playersList.rend(); 
				++rit
			){
				ss.str("");
				if(i<10)
					ss << "  " <<i++ << ") ";
				else
					ss << i++ << ") ";
					
				shifty += 23;
				
				ss << rit->second; 
				renderBitmapStringProjection( 
					-140, -10+shifty, 0,
					ss.str().c_str()
				);
				
				ss.str("");
				ss << rit->first; 
				renderBitmapStringProjection( 
					-140+shiftx, -10+shifty, 0,
					ss.str().c_str()
				);	
			}
			
		glPopMatrix();
	restorePerspectiveProjection();
}









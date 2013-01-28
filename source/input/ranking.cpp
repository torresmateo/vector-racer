
#include "ranking.hpp"


void Ranking::insert( string playerName, int score ){
	playersList.insert( std::pair<int,string>(score,playerName) );
	for (
		set< pair<int,string> >::iterator it=playersList.begin(); 
		playersList.size()>10;
		++it
	){ playersList.erase(it); }
}

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

void Ranking::setData(){
	fstream rankingFile("ranking (do not modify).txt",ios_base::in|ios_base::out|ios_base::trunc);
	
	for (
		set< pair<int,string> >::reverse_iterator rit=playersList.rbegin(); 
		rit != playersList.rend(); 
		++rit
	){ rankingFile << rit->second << '\n' << rit->first << '\n'; }
	
	rankingFile.close();
}

void Ranking::clear(){
	playersList.clear();
}

bool Ranking::isHighestScore( int score ){
	if( playersList.size() == 0 )
		return true;
		
	if( score > playersList.rbegin()->first )
		return true;
	
	return false;
}

bool Ranking::isTop10( int score ){
	if( playersList.size() < 10 )
		return true;
	
	if( score > playersList.begin()->first )
		return true;
	
	return false;
}

void Ranking::draw(){
	stringstream ss;
	int shifty = -40;
	int shiftx = 258;
	
	// preparacion para impresion en pantalla
	setOrthographicProjection();
		glPushMatrix();
			glLoadIdentity();
			glColor3f(CYAN);
			
			// ss << "Ranking";
			// renderBitmapStringProjection( 
				// 0, 40+shifty, 0,
				// ss.str().c_str()
			// );
			
			for (
				set< pair<int,string> >::reverse_iterator rit=playersList.rbegin(); 
				rit != playersList.rend(); 
				++rit
			){
				ss.str("");
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









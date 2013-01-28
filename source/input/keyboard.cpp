#include "keyboard.hpp"
//implementación de la clase Keyboard

//retorna un string con las teclas oprimidas
string Keyboard::toString(){
	
	stringstream ss;

    //se agregan las teclas ASCII
	ss << "{";
	
	for (set<unsigned char>::iterator it=asciiKeys.begin(); it!=asciiKeys.end(); ++it) {
		ss << (int)*it;
		ss << ",";
	}
	
    //se agregan las teclas compuestas
	ss << "} {";
	
	for (set<int>::iterator it=specialKeys.begin(); it!=specialKeys.end(); ++it) {
		ss << (int)*it;
		ss << ",";
	}
	
	ss << "}";
		
	return ss.str();
}

//retorna un string con las teclas ASCII oprimidas
string Keyboard::asciiToString(){
	
	stringstream ss;
	ss << "{";
	
	for (set<unsigned char>::iterator it=asciiKeys.begin(); it!=asciiKeys.end(); ++it) {
		ss << *it;
		ss << ",";
	}
	
	ss << "}";
		
	return ss.str();
}


bool Keyboard::keyPressed(){
	return asciiKeyPressed() or specialKeyPressed();
}


bool Keyboard::asciiKeyPressed(){
	return !asciiKeys.empty();
}
bool Keyboard::asciiKeyPressed( unsigned char key ){
	return asciiKeys.count( key )? true : false;
}


bool Keyboard::specialKeyPressed(){
	return !specialKeys.empty();
}
bool Keyboard::specialKeyPressed( int key ){
	return specialKeys.count( key )? true : false;
}


void Keyboard::insertAsciiKey( unsigned char key ){
	asciiKeys.insert(key);
}

void Keyboard::insertSpecialKey( int key ){
	specialKeys.insert(key);
}


void Keyboard::removeAsciiKey( unsigned char key ){
	asciiKeys.erase(key);
}

void Keyboard::removeSpecialKey( int key ){
	specialKeys.erase(key);
}


set<unsigned char> Keyboard::getAsciiKeyPresses(){
	return this->asciiKeys;
}

set<int> Keyboard::getSpecialKeyPresses(){
	return this->specialKeys;
}


unsigned char Keyboard::getNextAsciiKey(){
	unsigned char key = *(asciiKeys.begin());
	this->removeAsciiKey(key);
	return key;
}

int Keyboard::getNextSpecialKey(){
	int key = *(specialKeys.begin());
	this->removeSpecialKey(key);
	return key;
}























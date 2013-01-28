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

//retorna true si se esta presionando alguna tecla
bool Keyboard::keyPressed(){
	return asciiKeyPressed() or specialKeyPressed();
}

//retorna true si se esta presionando una tecla ASCII
bool Keyboard::asciiKeyPressed(){
	return !asciiKeys.empty();
}

//retorna true si la tecla ASCII "key" esta presionada
bool Keyboard::asciiKeyPressed( unsigned char key ){
	return asciiKeys.count( key )? true : false;
}

//retorna true si se esta presionando alguna tecla compuesta
bool Keyboard::specialKeyPressed(){
	return !specialKeys.empty();
}

//retorna true si la tecla compuesta "key" esta presionada
bool Keyboard::specialKeyPressed( int key ){
	return specialKeys.count( key )? true : false;
}

//inserta un caracer ASCII
void Keyboard::insertAsciiKey( unsigned char key ){
	asciiKeys.insert(key);
}

//inserta un caracter compuesto
void Keyboard::insertSpecialKey( int key ){
	specialKeys.insert(key);
}

//remueve un caracter ASCII
void Keyboard::removeAsciiKey( unsigned char key ){
	asciiKeys.erase(key);
}

//remueve un caracter compuesto
void Keyboard::removeSpecialKey( int key ){
	specialKeys.erase(key);
}

//retorna un set con los caracteres ASCII presionados
set<unsigned char> Keyboard::getAsciiKeyPresses(){
	return this->asciiKeys;
}

//retorna un set con los caracteres compuestos presionados
set<int> Keyboard::getSpecialKeyPresses(){
	return this->specialKeys;
}

//retorna el siguiente caracter ASCII del set
unsigned char Keyboard::getNextAsciiKey(){
	unsigned char key = *(asciiKeys.begin());
	this->removeAsciiKey(key);
	return key;
}

//retorna el siguiente caracter compuesto del set
int Keyboard::getNextSpecialKey(){
	int key = *(specialKeys.begin());
	this->removeSpecialKey(key);
	return key;
}























//clase Keyboard, para manejo del teclado

class Keyboard {
	
    //set para caracteras ASCII
	set<unsigned char> asciiKeys;
    //set para caracteres compuestos
	set<int> specialKeys;
	
	public:
	
        //insertar un caracter ASCII
		void insertAsciiKey( unsigned char );
        //insertar un caracter compuesto
		void insertSpecialKey( int );
	
        //remover un caracter ASCII
		void removeAsciiKey( unsigned char );
        //remover un caracter compuesto
		void removeSpecialKey( int );
		
        //devuelve el siguiente caracter ASCII
		unsigned char getNextAsciiKey();
        //devuelve el siguiente caracter compuesto
		int getNextSpecialKey();
		
        //devuelve un set con los caracteres ASCII que estan siendo presionados
		set<unsigned char> getAsciiKeyPresses();
        //devuelve un set con los caracteres compuestos que estan siendo presionados
		set<int> getSpecialKeyPresses();
		
        //devuelve true si hay alguna tecla que esta siendo presionada
		bool keyPressed();
        //devuelve true si hay alguna tecla ASCII que esta siendo presionada
		bool asciiKeyPressed();
        //devuelve true si la tecla ASCCI "key" esta siendo presionada
		bool asciiKeyPressed( unsigned char key );
        //devuelve true si hay alguna tecla compuesta que esta siendo presionada
		bool specialKeyPressed();
        //devuelve true si la tecla compuesta "key" esta siendo presionada
		bool specialKeyPressed( int key );
		
        //devuelve un string con las teclas presionadas
		string toString();
        //devuelve un string con las teclas ASCII presionadas
		string asciiToString();
		
};










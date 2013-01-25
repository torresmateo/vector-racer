

class Keyboard {
	
	set<unsigned char> asciiKeys;
	set<int> specialKeys;
	
	public:
	
		void insertAsciiKey( unsigned char );
		void insertSpecialKey( int );
	
		void removeAsciiKey( unsigned char );
		void removeSpecialKey( int );
		
		unsigned char getNextAsciiKey();
		int getNextSpecialKey();
		
		set<unsigned char> getAsciiKeyPresses();
		set<int> getSpecialKeyPresses();
		
		bool keyPressed();
		bool asciiKeyPressed();
		bool asciiKeyPressed( unsigned char key );
		bool specialKeyPressed();
		bool specialKeyPressed( int key );
		
		string toString();
		string asciiToString();
		
};










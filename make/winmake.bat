
cls
g++ -Wall -c -o main.o ..\source\include.cpp -I"C:\Program Files\Common Files\MinGW\freeglut\include"
g++ -o main.exe main.o "libirrKlang.a" -L"C:\Program Files\Common Files\MinGW\freeglut\lib" -lfreeglut -lglu32 -lopengl32


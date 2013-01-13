
if "%1" == "" goto ningunarg
if "%2" == "" goto unarg
goto dosarg

:ningunarg
cls
g++ -Wall -c -o main.o ..\source\include.cpp -I"C:\Program Files\Common Files\MinGW\freeglut\include"
g++ -o ..\main.exe main.o -L"C:\Program Files\Common Files\MinGW\freeglut\lib" -lfreeglut -lglu32 -lopengl32
goto end

:unarg
cls
g++ -Wall -c -o main.o ..\source\include.cpp -I"C:\Program Files\Common Files\MinGW\freeglut\include"
g++ -o ..\%1 main.o -L"C:\Program Files\Common Files\MinGW\freeglut\lib" -lfreeglut -lglu32 -lopengl32 -Wl,--subsystem,windows
goto end

:dosarg
cls
g++ -Wall -c -o main.o ..\source\%1 -I"C:\Program Files\Common Files\MinGW\freeglut\include"
g++ -o ..\%2 main.o -L"C:\Program Files\Common Files\MinGW\freeglut\lib" -lfreeglut -lglu32 -lopengl32 -Wl,--subsystem,windows
goto end

:end

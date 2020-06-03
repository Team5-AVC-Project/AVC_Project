#server makefile
INCLUDE = -I C:\SFML\SFML-2.5.1\include
LIBS = C:\SFML\SFML-2.5.1\lib
server3.exe: server3.o 
	g++ $(LIBS) -o server3 server3.o -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network
server3.o: server3.cpp 
	g++  -c $(INCLUDE) server3.cpp 

#robot makefile
INCLUDE = -I C:\SFML\SFML-2.5.1\include
LIBS = -L C:\SFML\SFML-2.5.1\lib
robot: robot.o 
	g++ $(LIBS) -o robot robot.o -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network
robot.o: robot.cpp 
	g++  -c $(INCLUDE) robot.cpp 


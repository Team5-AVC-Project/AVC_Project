INCLUDE = -I C:\SFML\SFML-2.5.1\include
LIBS = -L C:\SFML\SFML-2.5.1\lib
robot: robot.o 
	g++ $(LIBS) -o robot robot.o -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network
robot.o: robot.cpp 
	g++  -c $(INCLUDE) robot.cpp 



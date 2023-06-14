all: compile link clean

compile: 
	g++ -c Source/*.cpp -ISFML\include

link:
	g++ *.o -o Chess -LSFML\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	del *.o
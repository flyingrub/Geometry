all:
	g++ -g Main.cpp Vector.cpp Point.cpp Voxel.cpp Utils.cpp -lglut -lGL -lGLU -o main -std=c++11

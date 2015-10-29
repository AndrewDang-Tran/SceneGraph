

nothing: geom.h loader.h fileViewer.cpp Vertex.h Face.h Transform.h
	g++ -std=c++11 -o fileLoader fileViewer.cpp -lXext -lX11 -L/usr/lib/nvidia-340-updates -lGL -lGLU -lglut -lpthread
	fileLoader

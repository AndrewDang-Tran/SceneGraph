#nothing: geom.h loader.h fileViewer.cpp Vertex.h Face.h Transform.h
#	g++ -std=c++11 -o fileLoader fileViewer.cpp -lXext -lX11 -L/usr/lib/nvidia-340-updates -lGL -lGLU -lglut -lpthread
#	fileLoader
FILES = AttributeNode.c++ AttributeNode.h Camera.c++ Camera.h CameraNode.c++ CameraNode.h Face.c++ Face.h GeomNode.c++ GeomNode.h Gui.c++ Light.c++ Light.h LightNode.c++ LightNode.h Node.h ObjectNode.h SceneGraph.h SceneGraph.c++ Transform.c++ Transform.h TransformNode.h Vertex.c++ Vertex.h geom.h loader.h
CC = g++ -std=c++11
CFLAGS = -Wall -c
LFLAGS = -Wall

test: $(FILES)
	$(CC) $(LFLAGS) Gui.c++ -o test

clean:
	rm test test.txt
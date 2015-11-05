#nothing: geom.h loader.h fileViewer.cpp Vertex.h Face.h Transform.h
#	g++ -std=c++11 -o fileLoader fileViewer.cpp -lXext -lX11 -L/usr/lib/nvidia-340-updates -lGL -lGLU -lglut -lpthread
#	fileLoader
FILES = AttributeNode.c++ AttributeNode.h Camera.c++ Camera.h CameraNode.c++ CameraNode.h Face.c++ Face.h GeomNode.c++ GeomNode.h Gui.c++ Light.c++ Light.h LightNode.c++ LightNode.h Node.c++ Node.h ObjectNode.c++ ObjectNode.h SceneGraph.c++ SceneGraph.h Transform.c++ Transform.h TransformNode.h Vertex.c++ Vertex.h Geom.h Loader.h
CXXFILES = VectorMath.c++ Vertex.c++ Face.c++ Node.c++ Light.c++ Transform.c++ Camera.c++ Geom.c++ Loader.c++  AttributeNode.c++ CameraNode.c++ GeomNode.c++ LightNode.c++ ObjectNode.c++ SceneGraph.c++ Gui.c++
CXX = clang++ -std=c++11
STRINGFIX = -lXext -lX11 -L/usr/lib/nvidia-340-updates
GLUT = -lGL -lGLU -lglut -lpthread
GLUI = -L./glui-2.36/src/lib -lglui
LIBS = $(STRINGFIX) $(GLUT) $(GLUI)

test: $(FILES)
	$(CXX) $(CXXFILES) -o test $(LIBS) > test.txt 2>&1
	./test

clean:
	rm test test.txt
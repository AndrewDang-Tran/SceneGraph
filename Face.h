#include <vector>    //vector<Vertex>
#include "Vertex.h"

using namespace std;

class Face
{
	private:
		int triangleIndex[3];
		GLfloat normal[3];
		GLfloat centerCoordinates[3];

	public:
		Face(const int*& vertices);
		void setNormal(const GLfloat*& n);
		void computeCenter(const vector<Vertex>& vertices);
		void drawNormal() const;
		GLfloat* getNormal() { return normal; }
		int* getTriangleIndex() { return triangleIndex; }
};
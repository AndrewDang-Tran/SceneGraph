#include <stdlib.h>

class Vertex
{
	private:
		GLfloat coordinates[3];
		GLfloat normal[3];
		int numFaces;

	public:
		Vertex(const GLfloat*& c);
		void contributeNormal(const GLfloat*& n);
		void averageNormals();
		void drawNormal() const;
		const GLfloat*& getNormal() const { return normal; }
		const GLfloat*& getCoordinates() const { return coordinates; }
};

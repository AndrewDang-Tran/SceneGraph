#ifndef TRANSFORM_H
#define TRANSFORM_H

enum TransformType
{
	TRANSLATE,
	SCALE,
	ROTATE,
};

class Transform
{
	private:
		GLfloat args[4];
		TransformType type;

	public:
		Transform(const TransformType& t, const GLfloat*& a);
		void apply() const;
};

#endif
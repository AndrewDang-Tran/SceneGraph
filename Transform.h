
enum Type
{
	TRANSLATE,
	SCALE,
	ROTATE,
};

class Transform
{
	private:
		GLfloat args[4];
		Type type;

	public:
		Transform(const Type& t, const GLfloat*& a);
		void apply() const;
};

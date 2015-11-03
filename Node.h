#ifndef NODE_H
#define NODE_H

#include <vector> //children

using namespace std;

enum NodeType 
{
	OBJECT,
	GEOM,
	TRANSFORM,
	ATTRIBUTE,
	LIGHT,
	CAMERA,
};

//Base node class with typical n-tree parent child relations
class Node 
{
	private:
		vector<Node> children;
		static int staticCounter;
		int id;
	protected:
		Node* parent;
		NodeType type;
	public:
		Node();
		Node* addChild(const Node& child);
		void traverseChildren() const;
		virtual void execute() = 0;
		int getID();
};

#endif
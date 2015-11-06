#ifndef NODE_H
#define NODE_H

#include <cstddef> // NULL
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
		const Node* parent;
		NodeType type;
	public:
		Node();
		virtual void execute();
		int getID();
		Node* addChild(Node& child);
		void traverseChildren();
};

#endif

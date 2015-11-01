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
		Node* parent;
		vector<Node*> children;
		NodeType type;
		static int staticCounter;
		int id;
	public:
		Node();
		void addChild(const Node*& child);
		void traverseChildren(const Node* currentNode) const;
		virtual void execute() = 0;
};

#endif
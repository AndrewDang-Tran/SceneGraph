#ifndef NODE_H
#define NODE_H

#include <vector> //children

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
		Node() 
		{
			parent = NULL;
			staticCounter++;
			id = staticCounter;
		}
		void addChild(const Node*& child)
		{ 
			child->parent = this;
			children.push_back(child); 
		}
		virtual void execute() = 0;
};

#endif
#ifndef NODE_H
#define NODE_H

#define DEBUG

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
		vector<Node*> children;
		static int staticCounter;
		int id;
	protected:
		Node* parent;
		NodeType type;
	public:
		Node();
		virtual ~Node() = 0;
		virtual void execute();
		const int getID() const;
		const vector<Node*>& getChildren() const;
		void addChild(Node* child);
		void traverseChildren();
		const Node* getParent() const;
		Node* getParent();
		const NodeType getType() const;
		void removeChild(Node* targetChild);
};

#endif

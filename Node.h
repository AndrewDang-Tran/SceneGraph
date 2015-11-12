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
	ANIMATION,
	ATTRIBUTE,
	LIGHT,
	CAMERA,
};

/**
 * Base node class with typical n-tree parent child relations.
 */
class Node 
{
	private:
		vector<Node*> children;
		static int staticCounter; //Counter to ID each new node
		int id;
	protected:
		Node* parent;
		NodeType type;
	public:
		Node();
		virtual ~Node() = 0;
		/**
		 * Do the determined action for each node.
		 */
		virtual void execute();
		const int getID() const;
		const vector<Node*>& getChildren() const;
		void addChild(Node* child);
		/**
		 * Traverses through the scene graph starting from the calling node.
		 * Calls execute on each node it passes.
		 * Makes sure to push and pop the correct matrixes so not everything is effected by every transform.
		 */
		void traverseChildren();
		const Node* getParent() const;
		Node* getParent();
		const NodeType getType() const;
		void removeChild(Node* targetChild);
};

#endif

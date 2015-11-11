#ifndef OBJECTNODE_H
#define OBJECTNODE_H

#include <string> //name
#include "Node.h"

/**
 * ObjectNodes serve as a link between other objects, and groups them together
 * with a name.
 */
class ObjectNode : public Node 
{
	private:
		string name;
	public:
		ObjectNode(const string& n = string("World"));
		const string getName();
		/**
		 * Doesn't do anything for ObjectNodes.
		 */
		void execute();
		void setName(const string newName);
};

#endif
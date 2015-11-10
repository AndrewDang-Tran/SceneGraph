#ifndef OBJECTNODE_H
#define OBJECTNODE_H

#include <string> //name
#include "Node.h"

class ObjectNode : public Node 
{
	private:
		string name;
	public:
		ObjectNode(const string& n = string("World"));
		const string getName();
		void execute();
		void setName(const string newName);
};

#endif
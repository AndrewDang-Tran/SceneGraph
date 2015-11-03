#include "ObjectNode.h"

ObjectNode::ObjectNode(const string& n) : name(n) { type = OBJECT; }
string ObjectNode::getName() { return name; }
void ObjectNode::execute() {}

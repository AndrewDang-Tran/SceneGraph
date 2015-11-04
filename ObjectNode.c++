#include "ObjectNode.h"

ObjectNode::ObjectNode(const string& n = string("World")) : name(n) { type = OBJECT; }
const string ObjectNode::getName() { return name; }
void ObjectNode::execute() {}

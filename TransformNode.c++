#include "TransformNode.h"

TransformNode::TransformNode(const Transform& t) : transform(t) {}
void TransformNode::execute() { transform.apply(); }
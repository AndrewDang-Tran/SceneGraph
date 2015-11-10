#include "TransformNode.h"

TransformNode::TransformNode(const Transform& t) : transform(t) { type = TRANSFORM; }
void TransformNode::execute() { transform.apply(); }
void TransformNode::setParameters(const TransformType t, const GLfloat* a) {transform.changeArguments(t, a); }
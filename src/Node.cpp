#include "Node.hpp"


Node::Node(void) :
    ptr_(std::make_shared<Node*>(this))
{}

void Node::addChild(const NodeId& nodeId) {
    children_.emplace_back(nodeId.ptr());
}

NodeId Node::getId(void) {
    return NodeId(ptr_);
}

void Node::updatePtr(void) {
    *ptr_ = this;
}

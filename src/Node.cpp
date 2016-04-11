#include "Node.hpp"


Node::Node(unsigned id, const NodeId& parent) :
    id_(id),
    ptr_(std::make_shared<Node*>(this)),
    parent_(parent), size_(0)
{}

void Node::addChild(const NodeId& nodeId) {
    children_.emplace_back(nodeId.ptr());
    increaseSize();
}

NodeId Node::getId(void) {
    return NodeId(ptr_);
}

unsigned Node::getSize(void) const {
    return size_;
}

unsigned Node::getChildrenNumber(void) const {
    return children_.size();
}

void Node::updatePtr(void) {
    *ptr_ = this;
}

void Node::increaseSize(void) {
    ++size_;
    if (*parent_)
        parent_->increaseSize();
}

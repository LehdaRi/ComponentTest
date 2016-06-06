#include "Node.hpp"


unsigned Node::id__ = 0u;


void Node::addChild(const NodeId& nodeId) {
    //children_.push_back(nodeId);
    increaseSize();
}

NodeId Node::getId(void) const {
    return NodeId(it_);
}

unsigned Node::getSize(void) const {
    return size_;
}
/*
unsigned Node::getChildrenNumber(void) const {
    return children_.size();
}
*/
std::vector<Node>::iterator Node::getIterToNext(void) const {
    return it_->it+size_+1;
}

void Node::print(std::vector<Node>::iterator& it, unsigned level) {
    for (auto i=0u; i<level; ++i)
        printf("  ");

    if (parent_)
        printf("%u %u\n", id_, parent_->id_);
    else
        printf("%u\n", id_);
    it++;

    while (it < getIterToNext())
        it->print(it, level+1);
}

Node::Node(const NodeId& parent) :
    id_(id__++), it_(nullptr),
    parent_(parent), size_(0)
{}


void Node::increaseSize(void) {
    ++size_;
    if (parent_)
        parent_->increaseSize();
}

void Node::decreaseSize(unsigned n) {
    size_-=n;
    if (parent_)
        parent_->decreaseSize(n);
}

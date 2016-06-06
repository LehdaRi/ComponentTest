#include "Node.hpp"
#include "Scene.hpp"


Node::Node(uint64_t id, uint32_t level, const NodeId& parent) :
    id_(id),
    level_(level),
    valid_(std::make_shared<bool>(true)),
    active_(true),
    parent_(parent)
{
     printf("Node %u,%llu created\n", level_, id_);
}

bool Node::isValid(void) const {
    return *valid_;
}

NodeId Node::getId(void) const {
    return NodeId(id_, level_, valid_);
}
/*
unsigned Node::getSize(void) const {
    return size_;
}*/

unsigned Node::getChildrenNumber(void) const {
    return children_.size();
}
/*
std::vector<Node>::iterator Node::getIterToNext(void) const {
    return it_->it+size_+1;
}
*/
void Node::print(void) {
    for (auto i=0u; i<level_; ++i)
        printf("  ");

    printf("%u,%llu\n", level_, id_);

    for (auto& c : children_)
        if (c)
            (*c).print();
}


void Node::invalidate(void) {
    printf("Node %u,%llu invalidated\n", level_, id_);
    *valid_ = false;
    active_ = false;

    for (auto& c : children_)
        SCENE.deleteNode(c);

    children_.clear();
}

void Node::addChild(const NodeId& nodeId) {
    children_.push_back(nodeId);
}

/*
void Node::increaseSize(void) {
    ++size_;
    if (parent_)
        parent_->increaseSize();
}

void Node::decreaseSize(unsigned n) {
    size_-=n;
    if (parent_)
        parent_->decreaseSize(n);
}*/

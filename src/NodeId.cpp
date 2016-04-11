#include "NodeId.hpp"


NodeId::NodeId(void)// :
    //node_(nullptr)
{}

NodeId::NodeId(const std::shared_ptr<Node*>& node) :
    node_(node)
{}

Node* NodeId::operator*(void) const {
    if (node_)
        return *node_;
    return nullptr;
}

Node* NodeId::operator->(void) const {
    if (node_)
        return *node_;
    return nullptr;
}

Node* NodeId::ptr(void) {
    return *node_;
}

Node* NodeId::ptr(void) const {
    return *node_;
}

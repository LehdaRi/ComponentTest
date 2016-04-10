#include "NodeId.hpp"


NodeId::NodeId(const std::shared_ptr<Node*>& node) :
    node_(node)
{}

Node* NodeId::operator->(void) const {
    return *node_;
}

Node* NodeId::ptr(void) {
    return *node_;
}

Node* NodeId::ptr(void) const {
    return *node_;
}

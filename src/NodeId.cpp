#include "NodeId.hpp"
#include "Node.hpp"


NodeId::NodeId(void) :
    node_(nullptr)
{}

NodeId::NodeId(const std::shared_ptr<std::vector<Node>::iterator>& node) :
    node_(node)
{}

Node* NodeId::operator*(void) const {
    if (node_)
        return &**node_;
    return nullptr;
}

std::vector<Node>::iterator NodeId::operator->(void) const {
    return *node_;
}

NodeId::operator bool() const {
    return (bool)node_;
}

std::vector<Node>::iterator NodeId::iter(void) {
    return *node_;
}

std::vector<Node>::iterator NodeId::iter(void) const {
    return *node_;
}

Node* NodeId::ptr(void) {
    if (node_)
        return &**node_;
    return nullptr;
}

Node* NodeId::ptr(void) const {
    if (node_)
        return &**node_;
    return nullptr;
}

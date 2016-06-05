#include "NodeId.hpp"
#include "Node.hpp"


NodeId::NodeId(void) :
    node_(nullptr)
{}

NodeId::NodeId(const std::shared_ptr<Iter>& node) :
    node_(node)
{}

Node* NodeId::operator*(void) const {
    if (node_)
        return &*((*node_).it);
    return nullptr;
}

std::vector<Node>::iterator NodeId::operator->(void) const {
    return node_->it;
}

NodeId::operator bool() const {
    //printf("%p ",node_.get());
    return node_->valid;
}

std::vector<Node>::iterator NodeId::iter(void) {
    return node_->it;
}

std::vector<Node>::iterator NodeId::iter(void) const {
    return node_->it;
}

Node* NodeId::ptr(void) {
    if (node_)
        return &*((*node_).it);
    return nullptr;
}

Node* NodeId::ptr(void) const {
    if (node_)
        return &*((*node_).it);
    return nullptr;
}

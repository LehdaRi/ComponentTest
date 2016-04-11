#ifndef NODEID_HPP
#define NODEID_HPP


#include <memory>


class Node;


class NodeId {
public:
    friend class Scene;
    friend class Node;

    NodeId(void);
    NodeId(const std::shared_ptr<Node*>& node);

    //NodeId(const NodeId&)               = delete;
    //NodeId(NodeId&&)                    = delete;
    //NodeId& operator=(const NodeId&)    = delete;
    //NodeId& operator=(NodeId&&)         = delete;

    Node* operator*(void) const;
    Node* operator->(void) const;

    Node* ptr(void);
    Node* ptr(void) const;

private:
    std::shared_ptr<Node*> node_;
};


#endif // NODEID_HPP

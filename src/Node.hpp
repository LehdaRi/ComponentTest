#ifndef NODE_HPP
#define NODE_HPP


#include <unordered_map>
#include <vector>
#include <memory>

#include "NodeId.hpp"
#include "ComponentBase.hpp"
#include "TypeId.hpp"


class Node {
public:
    friend class Scene;

    Node(unsigned id = 0, const NodeId& parent = NodeId());

    void addChild(const NodeId& nodeId);

    template <typename T_Component>
    void addComponent(ComponentBase* component);

    NodeId getId(void);
    unsigned getSize(void) const;
    unsigned getChildrenNumber(void) const;

private:
    unsigned id_;   //temp?

    std::shared_ptr<Node*> ptr_;
    void updatePtr(void);

    NodeId parent_;
    unsigned size_; //number of subnodes
    void increaseSize(void);

    std::vector<Node*> children_;
    std::unordered_map<unsigned, std::vector<ComponentBase*>> components_;

};


template <typename T_Component>
void Node::addComponent(ComponentBase* component) {
    components_[TypeId::getTypeId<T_Component>()].push_back(component);
}


#endif  //  NODE_HPP

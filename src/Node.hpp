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

    Node(void);

    void addChild(const NodeId& nodeId);

    template <typename T_Component>
    void addComponent(ComponentBase* component);

    NodeId getId(void);

private:
    std::vector<Node*> children_;
    std::unordered_map<unsigned, std::vector<ComponentBase*>> components_;

    std::shared_ptr<Node*> ptr_;
    void updatePtr(void);
};


template <typename T_Component>
void Node::addComponent(ComponentBase* component) {
    components_[TypeId::getTypeId<T_Component>()].push_back(component);
}


#endif  //  NODE_HPP

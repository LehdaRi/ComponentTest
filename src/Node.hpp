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

    Node(uint64_t id, uint32_t level = 0u, const NodeId& parent = NodeId());

    bool isValid(void) const;
    NodeId getId(void) const;
    //unsigned getSize(void) const;
    unsigned getChildrenNumber(void) const;

    //  return iterator to next node of same level
    //std::vector<Node>::iterator getIterToNext(void) const;

    void print(void);    //TEMP

    /*template <typename T_Component>
    void setFirstComponent(int first);
    template <typename T_Component>
    void addComponent(void);*/

private:
    uint64_t id_;
    uint32_t level_;
    std::shared_ptr<bool> valid_;
    bool active_;

    NodeId parent_;
    //unsigned size_; //number of subnodes
    //void increaseSize(void);
    //void decreaseSize(unsigned n);

    std::vector<NodeId> children_;

    //  invalidation frees the node id and invalidates & deletes children
    void invalidate(void);

    //  adding children happens through Scene, therefore addChild is a private function
    void addChild(const NodeId& nodeId);

    /*struct ComponentInfo {
        int first;     //  iterator to first component
        unsigned n;         //  number of components in this node
        unsigned nTotal;    //  number of components in this node and subnodes
        ComponentInfo(void) : first(-1), n(0u), nTotal(0u) {}
    };
    //  Component infos stored with typeId
    std::unordered_map<unsigned, ComponentInfo> componentInfos_;
    //  for recursively increasing nTotal for parent nodes for specific component type
    template <typename T_Component>
    void addComponentTotal(void);*/
};
/*
template <typename T_Component>
void Node::setFirstComponent(int first) {
    componentInfos_[TypeId::getTypeId<T_Component>()].first = first;
}

template <typename T_Component>
void Node::addComponent(void) {
    auto& ci = componentInfos_[TypeId::getTypeId<T_Component>()];
    ++ci.n;
    ++ci.nTotal;
    parent_->addComponentTotal<T_Component>();
}

template <typename T_Component>
void Node::addComponentTotal(void) {
    ++componentInfos_[TypeId::getTypeId<T_Component>()].nTotal;
    parent_->addComponentTotal<T_Component>();
}
*/

#endif  //  NODE_HPP

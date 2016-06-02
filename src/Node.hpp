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

    NodeId getId(void) const;
    unsigned getSize(void) const;
    //unsigned getChildrenNumber(void) const;
    //  return iterator to next node of same level
    std::vector<Node>::iterator getIterToNext(void) const;

    void print(std::vector<Node>::iterator& it, unsigned level);

    /*template <typename T_Component>
    void setFirstComponent(int first);
    template <typename T_Component>
    void addComponent(void);*/


    unsigned id_;
private:
    static unsigned id__; //TEMP

    //  private constructor only for Scene to use
    Node(const NodeId& parent = NodeId());
    //  adding children happens through Scene, therefore addChild is a private function
    void addChild(const NodeId& nodeId);

    std::shared_ptr<std::vector<Node>::iterator> it_;

    NodeId parent_;
    unsigned size_; //number of subnodes
    void increaseSize(void);

    //std::vector<NodeId> children_;

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

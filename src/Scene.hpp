#ifndef SCENE_HPP
#define SCENE_HPP


#include "Node.hpp"
#include "Visitor.hpp"


class Scene {
public:
    Scene(unsigned nReservedNodes = 0u);

    NodeId addNode(void);
    NodeId addNode(const NodeId& parent);
    unsigned getNodesNumber(void) const;

    template <typename T_Component, typename... Args>
    T_Component& addComponent(const NodeId& node, Args&&... args);

    template <typename T_Visitor, typename T_Component>
    void operator()(Visitor<T_Visitor, T_Component>& visitor);

private:
    std::vector<Node> nodes_;
    void updateNodes(void);

    template <typename T_Component>
    std::vector<T_Component>& accessComponents(void);
};


template <typename T_Component, typename... Args>
T_Component& Scene::addComponent(const NodeId& node, Args&&... args) {
    auto& v = accessComponents<T_Component>();
    v.emplace_back(std::forward<Args>(args)...);

    T_Component& newComponent = v.back();

    node->addComponent<T_Component>(&newComponent);

    return newComponent;
}

template <typename T_Visitor, typename T_Component>
void Scene::operator()(Visitor<T_Visitor, T_Component>& visitor) {
    auto& v = accessComponents<T_Component>();

    for (auto& c : v)
        visitor(c);
}

template <typename T_Component>
std::vector<T_Component>& Scene::accessComponents(void) {
    static std::vector<T_Component> components;
    return components;
}


#endif  //  SCENE_HPP

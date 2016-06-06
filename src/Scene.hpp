#ifndef SCENE_HPP
#define SCENE_HPP


#include "Node.hpp"
#include "Visitor.hpp"


#define SCENE Scene::getInstance()


class Scene {
public:
    //  Scene is singleton class due to static component lists in accessComponents method
    static Scene& getInstance(void);
    Scene(const Scene&)             = delete;
    Scene(Scene&&)                  = delete;
    Scene& operator=(const Scene&)  = delete;
    Scene& operator=(Scene&&)       = delete;

    void reserveNodes(unsigned nReservedNodes);

    //  add top-level node
    NodeId addNode(void);
    //  add child node
    NodeId addNode(const NodeId& parent);

    void deleteNode(const NodeId& nodeId);
    unsigned getNodesNumber(void) const;

    void printNodes(void);  //TEMP

    template <typename T_Component, typename... Args>
    T_Component& addComponent(const NodeId& node, Args&&... args);

    //template <typename T_Visitor, typename T_Component>
    //void operator()(Visitor<T_Visitor, T_Component>& visitor);

private:
    Scene(void) {}

    std::vector<Node> nodes_;
    void updateNodes(std::vector<Node>::iterator it);

    //  access component vectors
    template <typename T_Component>
    std::vector<T_Component>& accessComponents(void);
};


template <typename T_Component, typename... Args>
T_Component& Scene::addComponent(const NodeId& node, Args&&... args) {
    auto& v = accessComponents<T_Component>();


}

/*
template <typename T_Visitor, typename T_Component>
void Scene::operator()(Visitor<T_Visitor, T_Component>& visitor) {
    auto& v = accessComponents<T_Component>();

    for (auto& c : v)
        visitor(c);
}
*/

template <typename T_Component>
std::vector<T_Component>& Scene::accessComponents(void) {
    static std::vector<T_Component> components;
    return components;
}


#endif  //  SCENE_HPP

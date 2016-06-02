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

    NodeId addNode(void);
    NodeId addNode(const NodeId& parent);
    void deleteNode(const NodeId& nodeId);
    unsigned getNodesNumber(void) const;

    void printNodes(void);

    //template <typename T_Component, typename... Args>
    //T_Component& addComponent(const NodeId& node, Args&&... args);

    //template <typename T_Visitor, typename T_Component>
    //void operator()(Visitor<T_Visitor, T_Component>& visitor);

private:
    Scene() {}

    std::vector<Node> nodes_;
    void updateNodes(std::vector<Node>::iterator it);

    //template <typename T_Component>
    //std::vector<T_Component>& accessComponents(void);
};


/*template <typename T_Component, typename... Args>
T_Component& Scene::addComponent(const NodeId& node, Args&&... args) {
    auto& v = accessComponents<T_Component>();
    auto& ci = node->componentInfos_[TypeId::getTypeId<T_Component>()];  // component info
    auto iter = v.begin();

    unsigned n = 0;
    if (ci.first < 0) {
        auto nodeIter = node.iter();
        while (nodeIter != nodes_.begin()) {
            auto& ci2 = nodeIter->componentInfos_[TypeId::getTypeId<T_Component>()];
            if (ci2.first >= 0) {
                n = ci2.first + ci2.n;
                break;
            }
        }
    }
    iter += n;

    v.emplace(iter, std::forward<Args>(args)...);

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
}*/


#endif  //  SCENE_HPP

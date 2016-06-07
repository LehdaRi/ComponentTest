#ifndef SCENE_HPP
#define SCENE_HPP


#include "Node.hpp"
#include "Visitor.hpp"


#define SCENE Scene::getInstance()


class Scene {
public:
    friend class NodeId;

    //  Scene is singleton class due to static component lists in accessComponents method
    static Scene& getInstance(void);
    Scene(const Scene&)             = delete;
    Scene(Scene&&)                  = delete;
    Scene& operator=(const Scene&)  = delete;
    Scene& operator=(Scene&&)       = delete;

    //void reserveNodes(unsigned nReservedNodes);

    //  add top-level node
    NodeId addNode(void);
    //  add child node
    NodeId addNode(const NodeId& parent);

    void deleteNode(const NodeId& nodeId);
    uint64_t getNodesNumber(int32_t level = -1);

    void printNodes(void);  //TEMP

    template <typename T_Component, typename... Args>
    T_Component& addComponent(const NodeId& node, Args&&... args);

    //template <typename T_Visitor, typename T_Component>
    //void operator()(Visitor<T_Visitor, T_Component>& visitor);

private:
    Scene(void);

    struct NodeLevel {
        std::vector<Node> nodes;
        int64_t firstFreeId;

        NodeLevel(void) : firstFreeId(-1) {}
    };

    inline static void updateFirstFreeId(NodeLevel& nodeLevel);

    static std::unordered_map<uint32_t, NodeLevel> nodes_;
    int64_t nTotalNodes;

    //  invalidation frees the node id and invalidates & deletes children
    void invalidateNode(Node& node);


    template<typename T_Component>
    struct ComponentLevel {
        std::vector<T_Component> components;
        int64_t firstFreeId;

        ComponentLevel(void) : firstFreeId(-1) {}
    };

    //  access component data structures
    template <typename T_Component>
    ComponentLevel<T_Component>& accessComponents(uint32_t level);

    template <typename T_Component>
    inline static void updateFirstFreeId(ComponentLevel<T_Component>& nodeLevel);
};


template <typename T_Component, typename... Args>
T_Component& Scene::addComponent(const NodeId& node, Args&&... args) {
    auto& cl = accessComponents<T_Component>(node.level_);

    if (cl.firstFreeId == -1) {
        cl.components.emplace_back(std::forward<Args>(args)...);

        return cl.components.back();
    }
    else {
        T_Component& c = cl.components[cl.firstFreeId];
        c = std::move(T_Component(std::forward<Args>(args)...));

        updateFirstFreeId(cl);
        return c;
    }
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
Scene::ComponentLevel<T_Component>& Scene::accessComponents(uint32_t level) {
    //  similar to nodes_ data structure, components are also ordered by levels
    static std::unordered_map<uint32_t, ComponentLevel<T_Component>> components;
    return components[level];
}

template <typename T_Component>
void Scene::updateFirstFreeId(Scene::ComponentLevel<T_Component>& componentLevel) {
    if (componentLevel.firstFreeId == -1)
        componentLevel.firstFreeId = 0;

    for (auto i=componentLevel.firstFreeId; i<(int64_t)componentLevel.components.size(); ++i) {
        if (!componentLevel.components[i].valid_) {
            componentLevel.firstFreeId = i;
            return;
        }
    }

    componentLevel.firstFreeId = -1;
}


#endif  //  SCENE_HPP

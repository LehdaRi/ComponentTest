#ifndef SCENE_HPP
#define SCENE_HPP


#include "Node.hpp"
#include "Visitor.hpp"

#include <map>


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

    static std::map<uint32_t, NodeLevel> nodes_;
    int64_t nTotalNodes;

    //  invalidation frees the node id and invalidates & deletes children
    void invalidateNode(Node& node);

/*
    template<typename T_Component>
    struct ComponentLevel {
        std::vector<T_Component> components;
        int64_t firstFreeId;

        ComponentLevel(void) : firstFreeId(-1) {}
    };
*/



    //  access component data structures
    template <typename T_Component>
    std::vector<T_Component>& accessComponents(uint32_t level);

    //  first free ids using type id system. unordered_map for type ids, map for levels
    std::unordered_map<uint32_t, std::map<uint32_t, int64_t>> componentFirstFreeIds_;

    template <typename T_Component>
    void updateComponentPointers(void);
};


template <typename T_Component, typename... Args>
T_Component& Scene::addComponent(const NodeId& node, Args&&... args) {
    auto& cv = accessComponents<T_Component>(node.level_);

    //  type Id
    auto typeId = ComponentBase::getTypeId<T_Component>();
    //  level map of first free ids
    auto& ffIdLevel = componentFirstFreeIds_[typeId];
    //  if specified level has no components, initialize first free id to -1
    if (ffIdLevel.find(node.level_) == ffIdLevel.end())
        ffIdLevel[node.level_] = -1;

    auto& ffId = ffIdLevel[node.level_];

    if (ffId == -1) {
        auto cap1 = cv.capacity();
        cv.emplace_back(std::forward<Args>(args)...);
        auto cap2 = cv.capacity();

        (*node).setComponent<T_Component>(&cv.back(), cv.size()-1);

        if (cap2 > cap1) {
            printf("Component vector capacity on level %u increased to %llu, updating pointers...\n", node.level_, cap2);
            updateComponentPointers<T_Component>();
        }

        return cv.back();
    }
    else {
        printf("Component %i on level %u revalidated\n", ffId, node.level_);
        T_Component& c = cv[ffId];
        c = std::move(T_Component(std::forward<Args>(args)...));

        (*node).setComponent<T_Component>(&c, ffId);

        //  find next free id
        ffId = -1;
        for (auto i=ffId+1; i<(int64_t)cv.size(); ++i) {
            if (!cv[i].valid_) {
                ffId = i;
                break;
            }
        }

        return c;
    }
}

template <typename T_Component>
std::vector<T_Component>& Scene::accessComponents(uint32_t level) {
    //  similar to nodes_ data structure, components are also ordered by levels
    static std::map<uint32_t, std::vector<T_Component>> components;
    return components[level];
}

template <typename T_Component>
void Scene::updateComponentPointers(void) {
    uint32_t l = 0;

    for (auto& nl : nodes_) {
        auto& cv = accessComponents<T_Component>(l++);

        for (auto& n : nl.second.nodes)
            if (n.hasComponent<T_Component>())
                n.updateComponentPointer(cv);
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


#endif  //  SCENE_HPP

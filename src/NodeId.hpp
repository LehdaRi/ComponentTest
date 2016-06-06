#ifndef NODEID_HPP
#define NODEID_HPP


#include <cstdint>
#include <unordered_map>
#include <vector>
#include <memory>


class Node;


class NodeId {
public:
    friend class Scene;

    NodeId(void);
    NodeId(uint64_t id, uint32_t level, const std::shared_ptr<bool>& valid);

    //Node* operator*(void) const;
    //std::vector<Node>::iterator operator->(void) const;

    Node& operator*(void) const;
    operator bool() const;

    //Node* ptr(void);
    //Node* ptr(void) const;

private:
    uint64_t id_;
    uint32_t level_;
    std::shared_ptr<bool> valid_;
};


#endif // NODEID_HPP

#ifndef NODEID_HPP
#define NODEID_HPP


#include <memory>
#include <vector>


class Node;


class NodeId {
public:
    struct Iter {
        std::vector<Node>::iterator it;
        bool valid;

        Iter(void) : valid(false) {}
        Iter(const std::vector<Node>::iterator it) : it(it), valid(true) {}
    };

    friend class Scene;
    friend class Node;

    NodeId(void);
    NodeId(const std::shared_ptr<Iter>& node);

    Node* operator*(void) const;
    std::vector<Node>::iterator operator->(void) const;

    operator bool() const;

    std::vector<Node>::iterator iter(void);
    std::vector<Node>::iterator iter(void) const;

    Node* ptr(void);
    Node* ptr(void) const;

    std::shared_ptr<Iter> node_;
private:
    //std::shared_ptr<std::vector<Node>::iterator> node_;
};


#endif // NODEID_HPP

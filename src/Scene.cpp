#include "Scene.hpp"


#include <chrono>
#include <iostream>
#include <deque>


Scene& Scene::getInstance(void) {
    static Scene instance;
    return instance;
}

void Scene::reserveNodes(unsigned nReservedNodes) {
    nodes_.reserve(nReservedNodes);
}

NodeId Scene::addNode(void) {
    auto c1 = nodes_.capacity();
    nodes_.push_back(std::move(Node()));
    auto& newNode = nodes_.back();
    //  give node the iterator to itself
    newNode.it_ = std::make_shared<std::vector<Node>::iterator>(nodes_.end()-1);
    auto c2 = nodes_.capacity();

    //  if vector has got reallocated, update node iterators
    if (c2 > c1)
        updateNodes(nodes_.begin());

    return newNode.getId();
}

NodeId Scene::addNode(const NodeId& parent) {
    auto c1 = nodes_.capacity();

    //  add new node before the next node of same level than parent
    auto newNodeIt = nodes_.insert(parent->getIterToNext(), std::move(Node(parent)));
    //  give node the iterator to itself
    newNodeIt->it_ = std::make_shared<std::vector<Node>::iterator>(newNodeIt);

    auto c2 = nodes_.capacity();

    //  if vector has got reallocated, update all node iterators
    if (c2 > c1)
        updateNodes(nodes_.begin());
    else    //  all following nodes need updating nevertheless
        updateNodes(newNodeIt+1);

    //  add child to parent, has to be done after iterator update
    auto newNodeId = newNodeIt->getId();
    parent->addChild(newNodeId);

    return newNodeId;
}

void Scene::deleteNode(const NodeId& nodeId) {
    if (nodeId->parent_)
        nodeId->parent_->decreaseSize(nodeId->getSize()+1);
    updateNodes(nodes_.erase(nodeId.iter(), nodeId->getIterToNext()));
}

unsigned Scene::getNodesNumber(void) const {
    return nodes_.size();
}

void Scene::printNodes(void) {
    for (auto it = nodes_.begin(); it < nodes_.end();) {
        it->print(it, 0);
    }
}
void Scene::updateNodes(std::vector<Node>::iterator it) {
    //auto start = std::chrono::steady_clock::now();

    for (; it != nodes_.end(); ++it) {
        //auto ptr = std::make_shared<std::vector<Node>::iterator>(it);
        //printf("%p\n", &**ptr);
        *(it->it_) = it;
    }

    //auto end = std::chrono::steady_clock::now();
    //auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    //std::cout << "node update: " << diff.count() << " microseconds" << std::endl;
}

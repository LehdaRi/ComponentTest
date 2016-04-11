#include "Scene.hpp"


#include <chrono>
#include <iostream>


unsigned Scene::nodeId__ = 0;


Scene::Scene(unsigned nReservedNodes) {
    nodes_.reserve(nReservedNodes);
}

NodeId Scene::addNode(void) {
    auto c1 = nodes_.capacity();
    //printf("adding new node: %u\n", nodeId__);
    nodes_.emplace_back(nodeId__++);
    auto c2 = nodes_.capacity();

    //  if vector has got reallocated, update node pointers
    if (c2 > c1)
        updateNodes(nodes_.begin());

    NodeId nodeId = nodes_.back().getId();

    return nodeId;
}

NodeId Scene::addNode(const NodeId& parent) {
    int offset = (parent.ptr()-&nodes_.front())+parent->getSize()+1;
    NodeId nodeId;

    if (offset-nodes_.size() == 0) {
        auto c1 = nodes_.capacity();
        nodes_.emplace_back(nodeId__++, parent);
        auto c2 = nodes_.capacity();

        if (c2 > c1)
            updateNodes(nodes_.begin());

        nodeId = nodes_.back().getId();
    }
    else {
        auto c1 = nodes_.capacity();
        auto iter = nodes_.insert(nodes_.begin()+offset, Node(nodeId__++, parent));
        auto c2 = nodes_.capacity();

        if (c2 > c1)
            updateNodes(nodes_.begin());
        else
            updateNodes(iter);

        nodeId = iter->getId();
    }

    parent->addChild(nodeId);

    return nodeId;
}

unsigned Scene::getNodesNumber(void) const {
    return nodes_.size();
}

void Scene::updateNodes(std::vector<Node>::iterator start) {
    //auto start = std::chrono::steady_clock::now();

    for (; start != nodes_.end(); ++start)
        start->updatePtr();

    //auto end = std::chrono::steady_clock::now();
    //auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    //std::cout << "node update: " << diff.count() << " microseconds" << std::endl;
}

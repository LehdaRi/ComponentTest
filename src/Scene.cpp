#include "Scene.hpp"


#include <chrono>
#include <iostream>


Scene::Scene(unsigned nReservedNodes) {
    nodes_.reserve(nReservedNodes);
}

NodeId Scene::addNode(void) {
    auto c1 = nodes_.capacity();
    nodes_.emplace_back();
    auto c2 = nodes_.capacity();

    //  if vector has got reallocated, update node pointers
    if (c2 > c1)
        updateNodes();

    NodeId nodeId = nodes_.back().getId();

    return nodeId;
}

NodeId Scene::addNode(const NodeId& parent) {
    NodeId nodeId = addNode();
    parent->addChild(nodeId);

    return nodeId;
}

unsigned Scene::getNodesNumber(void) const {
    return nodes_.size();
}

void Scene::updateNodes(void) {
    //auto start = std::chrono::steady_clock::now();

    for (auto& node : nodes_)
        node.updatePtr();

    //auto end = std::chrono::steady_clock::now();
    //auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    //std::cout << "node update: " << diff.count() << " microseconds" << std::endl;
}

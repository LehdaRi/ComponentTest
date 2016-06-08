#include <iostream>
#include <chrono>
#include <random>

#include "Scene.hpp"
#include "TestComponents.hpp"


void addComponents(std::default_random_engine& r, NodeId& node) {
    if (r()%3 == 0)
        SCENE.addComponent<TCA>(node, r()%100, r()%100);
    if (r()%3 == 0)
        SCENE.addComponent<TCB>(node, (r()%1000)/100.0f, (r()%10000)/100.0);
}

bool addNodes(std::default_random_engine& r, std::vector<NodeId>& nodes,
              const NodeId& parent, int min, int max) {
    int n = min + r()%(max-min+1);

    for (auto i=0; i<n; ++i) {
        auto id = SCENE.addNode(parent);
        nodes.push_back(id);

        addComponents(r, id);

        if (SCENE.getNodesNumber() >= 1000)
            return false;

        addNodes(r, nodes, id, min-1<=0 ? 0 : min-1, max-1);
    }
    return true;
}

void buildRandomScene(std::default_random_engine& r, std::vector<NodeId>& nodes) {
    for (auto i=0u; i<1000u; ++i) {
        auto id = SCENE.addNode();

        addComponents(r, id);

        nodes.push_back(id);

        if (!addNodes(r, nodes, id, 2, 8))
            break;
    }
}

void deleteRandomNodes(std::default_random_engine& r, std::vector<NodeId>& nodes) {
    while (true) {
        for (auto it = nodes.begin(); it != nodes.end();) {
            if (r()%10 == 0) {
                SCENE.deleteNode(*it);
                it = nodes.erase(it);
                if (SCENE.getNodesNumber() <= 500)
                    return;
            }
            else
                ++it;
        }
    }
}

int main(void) {
    std::default_random_engine r(715517);
    std::vector<NodeId> nodes;
/*
    nodes.push_back(SCENE.addNode());
    nodes.push_back(SCENE.addNode(nodes[0]));
    nodes.push_back(SCENE.addNode(nodes[0]));
    nodes.push_back(SCENE.addNode(nodes[0]));
    nodes.push_back(SCENE.addNode(nodes[2]));
    nodes.push_back(SCENE.addNode());
    nodes.push_back(SCENE.addNode());
    nodes.push_back(SCENE.addNode(nodes[6]));

    SCENE.printNodes();

    SCENE.addComponent<TCA>(nodes[1], 4, 5);
    SCENE.addComponent<TCA>(nodes[2], 6, 7);
    SCENE.addComponent<TCA>(nodes[4], 1, 2);
    SCENE.addComponent<TCA>(nodes[7], 8, 6);
    SCENE.addComponent<TCB>(nodes[0], 4, 5);
    SCENE.addComponent<TCB>(nodes[2], 6, 7);
    SCENE.addComponent<TCB>(nodes[4], 1, 2);
    SCENE.addComponent<TCB>(nodes[5], 8, 6);

    SCENE.deleteNode(nodes[2]);

    auto& cr5 = SCENE.addComponent<TCA>(nodes[3], 8, 12);
    auto& cr6 = SCENE.addComponent<TCB>(nodes[7], 45, 1);
*/


    for (auto i=0u; i<1; ++i) {
        buildRandomScene(r, nodes);
        //SCENE.printNodes();
        //printf("Number of nodes: %llu\n", SCENE.getNodesNumber());
        deleteRandomNodes(r, nodes);
    }

    SCENE.printNodes();
    printf("Number of nodes: %llu\n", SCENE.getNodesNumber());

    buildRandomScene(r, nodes);
    SCENE.printNodes();
    printf("Number of nodes: %llu\n", SCENE.getNodesNumber());


/*
    TVA visitor;

    auto start = std::chrono::steady_clock::now();
    buildRandomScene(scene, r);
    auto end = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout << "scene build: " << diff.count() << " microseconds" << std::endl;

    float avg = 0.0f;
    for (auto i=0; i<100; ++i) {
        auto start = std::chrono::steady_clock::now();

        scene(visitor);

        auto end = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
        //std::cout << "component list: " << diff.count() << " microseconds" << std::endl;
        avg += diff.count();
    }
    avg /= 100.0f;

    printf("static average: %0.3f microseconds\n", avg);
*/

    return 0;
}

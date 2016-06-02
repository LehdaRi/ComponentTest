#include <iostream>
#include <chrono>
#include <random>

#include "Scene.hpp"


void addNodes(std::default_random_engine& r, std::vector<NodeId>& nodes,
              const NodeId& parent, int min, int max) {
    int n = min + r()%(max-min+1);

    for (auto i=0; i<n; ++i) {
        auto id = SCENE.addNode(parent);
        nodes.push_back(id);
        addNodes(r, nodes, id, min-1<=0 ? 0 : min-1, max-1);
    }
}

void buildRandomScene(std::default_random_engine& r, std::vector<NodeId>& nodes) {
    for (auto i=0u; i<4u; ++i) {
        auto id = SCENE.addNode();
        nodes.push_back(id);
        addNodes(r, nodes, id, 1, 3);
    }
}

int main(void) {
    //SceneTester st(715517, 100000, 50);

    //st.test();

    std::default_random_engine r(715517);
    std::vector<NodeId> nodes;
    buildRandomScene(r, nodes);
    SCENE.printNodes();

    for (auto& node : nodes) {
        if (r()%5 == 0) {
            printf("deleting node %u\n", node->id_);
            SCENE.deleteNode(node);
        }
    }

    SCENE.printNodes();

    /*TVA visitor;

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

    printf("static average: %0.3f microseconds\n", avg);*/

    return 0;
}

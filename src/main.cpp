#include <iostream>
#include <chrono>
#include <random>

#include "Scene.hpp"


bool addNodes(std::default_random_engine& r, std::vector<NodeId>& nodes,
              const NodeId& parent, int min, int max) {
    int n = min + r()%(max-min+1);

    for (auto i=0; i<n; ++i) {
        auto id = SCENE.addNode(parent);
        nodes.push_back(id);
        if (nodes.size() >= 10)
            return false;
        addNodes(r, nodes, id, min-1<=0 ? 0 : min-1, max-1);
    }
    return true;
}

void buildRandomScene(std::default_random_engine& r, std::vector<NodeId>& nodes) {
    for (auto i=0u; i<1000u; ++i) {
        auto id = SCENE.addNode();
        nodes.push_back(id);
        if (!addNodes(r, nodes, id, 1, 3))
            break;
    }
}

void deleteRandomNodes(std::default_random_engine& r, std::vector<NodeId>& nodes) {
    //while (true) {
        for (auto it = nodes.begin(); it != nodes.end();) {
            //if (r()%5 == 0) {
                //if ((*it)->id_ == 100)
                    //printf("DBG\n");
                printf("deleting node %u\n", (*it)->id_);
                //SCENE.deleteNode(*it);
                it = nodes.erase(it);
                //if (nodes.size() <= 50)
                    //return;
            //}
            //else
                //++it;
        }
    //}
}

int main(void) {
    //SceneTester st(715517, 100000, 50);

    //st.test();

    std::default_random_engine r(715517);
    std::vector<NodeId> nodes;

    auto id = SCENE.addNode();
    printf("%p %p\n", id.node_.get(), id->it_.get());
    SCENE.deleteNode(id);
    printf("%p %p\n", id.node_.get(), id->it_.get());
    //printf("%u\n", id->id_);

    buildRandomScene(r, nodes);

    for (auto& node : nodes)
        if (node)
            printf("%u ", node->id_);
    printf("\n\n");

    SCENE.printNodes();
    SCENE.deleteNode(nodes[1]);

    for (auto& node : nodes)
        if (node)
            printf("%u ", node->id_);
    printf("\n\n");
*/
    //deleteRandomNodes(r, nodes);
    //SCENE.printNodes();


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

#include <iostream>
#include <chrono>
#include <random>

#include "Scene.hpp"


void addNodes(std::default_random_engine& r, const NodeId& parent, int min, int max) {
    int n = min + r()%(max-min+1);

    for (auto i=0u; i<n; ++i) {
        auto id = SCENE.addNode(parent);
        addNodes(r, id, min-1<=0 ? 0 : min-1, max-1);
    }
}

void buildRandomScene() {
    std::default_random_engine r(715517);
    for (auto i=0u; i<4u; ++i) {
        auto id = SCENE.addNode();
        addNodes(r, id, 2, 5);
    }
}

int main(void) {
    //SceneTester st(715517, 100000, 50);

    //st.test();

    buildRandomScene();
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

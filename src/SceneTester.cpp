#include "SceneTester.hpp"
#include "Clock.hpp"


SceneTester::SceneTester(unsigned seed, unsigned nNodes, unsigned nLevels) :
    scene_(nNodes),
    r_(seed), nNodesMax_(nNodes), nNodes_(0), nLevels_(nLevels),
    adding_(true), level_(0)
{
    Clock clock;
    clock.begin();
    while (adding_) {
        auto newNode = scene_.addNode();
        ++nNodes_;
        nNodesPerLevel_[0]++;

        auto min = r_()%2;
        auto max = min + r_()%3;

        ++level_;
        if (nLevels_ > 1)
            addChildren(newNode, min, max);
        --level_;
    }
    clock.end("Building a scene: ", Clock::MILLISECONDS);

    for (auto& l : nNodesPerLevel_)
        printf("  Nodes on level %u: %u\n", l.first, l.second);
}

void SceneTester::test(void) {
    TVA visitor1;
    TVB visitor2;

    Clock clock;
    clock.begin();
    scene_(visitor1);
    clock.end("TestComponent A Visitor: ", Clock::MICROSECONDS);

    clock.begin();
    scene_(visitor2);
    clock.end("TestComponent B Visitor: ", Clock::MICROSECONDS);
}

const Scene& SceneTester::getScene(void) const {
    return scene_;
}

void SceneTester::addChildren(NodeId& node, unsigned min, unsigned max) {
    if (max == 0 || max < min)
        return;

    auto n = min + r_()%(max-min+1);
    for (auto i=0u; i<n && adding_; ++i) {
        auto newNode = scene_.addNode(node);
        ++nNodes_;
        nNodesPerLevel_[level_]++;

        auto newMin = r_()%10;
        auto newMax = newMin + r_()%15;
        addRandomComponents(newNode, newMin, newMax);

        if (scene_.getNodesNumber() >= nNodes_) {
            adding_ = false;
            break;
        }

        if (level_ >= nLevels_)
            break;

        newMin = r_()%2;
        newMax = newMin + r_()%3;
        ++level_;
        addChildren(newNode, newMin, newMax);
        --level_;
    }
}

void SceneTester::addRandomComponents(NodeId& node, unsigned min, unsigned max) {
    if (max == 0 || max < min)
        return;

    auto nComponents = min + r_()%(max-min+1);
    //printf("adding %u random components\n", nComponents);
    for (auto i=0u; i<nComponents; ++i) {
        if (r_()%2)
            scene_.template addComponent<TCA>(node, -100+r_()%200, -100+r_()%200);
        else
            scene_.template addComponent<TCB>(node, (-1000+r_()%2000)*0.1f, (-10000+r_()%20000)*0.01);
    }
}

#ifndef SCENETESTER_HPP
#define SCENETESTER_HPP


#include "Scene.hpp"
#include "TestComponents.hpp"
#include "TestVisitors.hpp"

#include <random>
#include <map>


class SceneTester {
public:
    SceneTester(unsigned seed, unsigned nNodes, unsigned nLevels);

    void test(void);

    const Scene& getScene(void) const;

private:
    Scene scene_;
    std::default_random_engine r_;
    unsigned nNodesMax_, nNodes_, nLevels_;
    std::map<unsigned, unsigned> nNodesPerLevel_;

    //Scene build variables
    bool adding_;
    unsigned level_;
    void addChildren(NodeId& node, unsigned min, unsigned max);
    void addRandomComponents(NodeId& node, unsigned min, unsigned max);
};


#endif // SCENETESTER_HPP

#ifndef TESTVISITORS_HPP
#define TESTVISITORS_HPP


#include "Visitor.hpp"


class TVA : public Visitor<TVA, TCA> {
public:
    void operator()(TCA& component) {
        ++component.a_;
        --component.b_;
    }
};


class TVB : public Visitor<TVB, TCB> {
public:
    void operator()(TCB& component) {
        component.a_ *= 1.01f;
        component.b_ /= 1.02;
    }
};


#endif // TESTVISITORS_HPP

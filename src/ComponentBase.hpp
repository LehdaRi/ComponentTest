#ifndef COMPONENTBASE_HPP
#define COMPONENTBASE_HPP


class ComponentBase {
public:
    friend class Scene;

    ~ComponentBase(void) {};

private:
    bool active_;
};


#endif  //  COMPONENTBASE_HPP

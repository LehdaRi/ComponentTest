#ifndef TYPEID_HPP
#define TYPEID_HPP


class TypeId {
public:
    //type-id information
    template <typename T>
    static unsigned getTypeId(void);

private:
    static unsigned typeIdCounter__;
};


template <typename T>
unsigned TypeId::getTypeId(void) {
    static unsigned typeId = typeIdCounter__++;
    return typeId;
}


#endif // TYPEID_HPP

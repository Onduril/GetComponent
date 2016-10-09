#include "Component.h"
#include "Entity.h"
#include "GSL.h"

class Comp1 : public Component
{
public:
    DECLARE_COMPONENT(Comp1, Component);
};

class Comp2 : public Component
{
public:
    DECLARE_COMPONENT(Comp2, Component);
};

class Comp3 : public Component
{
public:
    DECLARE_COMPONENT(Comp3, Component);
};

class Comp4 : public Component
{
public:
    DECLARE_COMPONENT(Comp4, Component);
};

class Comp11 : public Comp1
{
public:
    DECLARE_COMPONENT(Comp11, Comp1);
};

class Comp12 : public Comp1
{
public:
    DECLARE_COMPONENT(Comp12, Comp1);
};

class Comp21 : public Comp2
{
public:
    DECLARE_COMPONENT(Comp21, Comp2);
};

class Comp211 : public Comp21
{
public:
    DECLARE_COMPONENT(Comp211, Comp21);
};

class Comp212 : public Comp21
{
public:
    DECLARE_COMPONENT(Comp212, Comp21);
};

template <typename T>
__declspec(noinline) T * testGetComponent(Entity & e)
{
    return e.getComponent<T>();
}

void Component::test()
{
    Component::registerIdInfo<Comp212>();
    Component::registerIdInfo<Comp12>();
    Component::registerIdInfo<Comp11>();
    Component::registerIdInfo<Comp4>();
    Component::registerIdInfo<Comp3>();
    Component::registerIdInfo<Comp12>();
    Component::registerIdInfo<Comp2>();
    Component::registerIdInfo<Comp211>();
    Component::registerIdInfo<Comp1>();

    Entity e;
    e.addComponent<Comp21>();
    e.addComponent<Comp212>();
    e.addComponent<Comp3>();
    e.addComponent<Comp11>();
    e.addComponent<Comp12>();

    Expects(nullptr == e.getComponent<Comp211>());

    #define TEST_COMPONENT_NAME(name, realName) \
        Expects(std::string(#realName) == testGetComponent<name>(e)->getName())

    // get direct
    TEST_COMPONENT_NAME(Comp212, Comp212);
    TEST_COMPONENT_NAME(Comp21, Comp21);
    TEST_COMPONENT_NAME(Comp3, Comp3);
    TEST_COMPONENT_NAME(Comp11, Comp11);
    TEST_COMPONENT_NAME(Comp12, Comp12);

    // get base class
    TEST_COMPONENT_NAME(Component, Comp21); // we get the first
    TEST_COMPONENT_NAME(Comp21, Comp21);
    TEST_COMPONENT_NAME(Comp1, Comp11);
}

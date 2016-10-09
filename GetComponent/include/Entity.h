#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>
#include <memory>
#include <utility>
#include <gsl.h>
#include "Component.h"

using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::move;
using std::forward;

class Entity
{
public:

    static void test();

    template <typename C, typename... Args>
    void addComponent(Args &&... args);

    template <typename C>
    C * getComponent() const;

private:

    Component * getComponent(Component::Id _id, Component::Id _mask) const;

    vector<unique_ptr<Component>> m_components;
    vector<Component::Id> m_componentIds;      // invariant : m_components.size() == m_componentIds.size()
};

template<typename C, typename ...Args>
inline void Entity::addComponent(Args && ...args)
{
    Expects(IdInfoOf<C>::value.isRegistered() != 0);
    m_components.emplace_back(make_unique<C>(forward<Args>(args)...));
    m_componentIds.emplace_back(IdInfoOf<C>::value.getId());
}

template<typename C>
inline C * Entity::getComponent() const
{
    auto & idInfo = IdInfoOf<C>::value;
    auto id = idInfo.getId();
    auto mask = idInfo.getMaskId();
    return static_cast<C*>(getComponent(id, mask));
}

#endif // ENTITY_H_

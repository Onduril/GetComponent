#include "Entity.h"
#include "Component.h"


Component * Entity::getComponent(Component::Id idSearched, Component::Id mask) const
{
    auto itFound = std::find_if(begin(m_componentIds), end(m_componentIds), [&](auto id) { return (id & mask) == idSearched; });
    if (itFound != end(m_componentIds))
    {
        auto idx = itFound - begin(m_componentIds);
        return m_components[idx].get();
    }
    return nullptr;
}

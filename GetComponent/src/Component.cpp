#include "Component.h"
#include "gsl.h"

using uint_t = unsigned int;

// can be improved (use intrinsic or bit tweak)
inline uint_t getNbBitNeeded(Component::Id v)
{
    uint_t nbBit = 0;

    for (; v != 0; v >>= 1)
    {
        nbBit++;
    }
    return nbBit;
}


void Component::IdInfo::addChildren(IdInfo & id)
{
    if (std::find(begin(m_children), end(m_children), &id) != end(m_children))
        return;

    m_children.emplace_back(&id);
    buildChildrenIds();
}

void Component::IdInfo::buildIds(IdInfo & parent)
{
    auto & brotherList = parent.m_children;
    Expects(std::find(begin(brotherList), end(brotherList), this) != end(brotherList));
    auto nbBrother = brotherList.size();
    auto nbParentBit = getNbBitNeeded(parent.m_idMask);
    auto nbBit = nbParentBit + getNbBitNeeded(nbBrother);
    auto brotherIdx = 1 + std::find(begin(brotherList), end(brotherList), this) - begin(brotherList); // add 1 as 0 is the mark of "missing" to handle inheritence
    m_idMask = (Id(1) << nbBit) - Id(1);
    m_id = parent.m_id | (brotherIdx << nbParentBit);
    Expects(m_id != parent.m_id); // to handle inheritence, the id has to be different than the parent one
    Expects((m_id & m_idMask) == m_id); // overrun the Id nb bit
    buildChildrenIds();
}

void Component::IdInfo::buildChildrenIds()
{
    for(auto idInfo : m_children)
    {
        idInfo->buildIds(*this);
    }
}


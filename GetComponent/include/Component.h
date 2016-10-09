#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <vector>

using std::vector;

#define DECLARE_COMPONENT(name, parentName)                                \
    public:                                                                \
        static IdInfo & getIdInfo()                                        \
        {                                                                  \
            static IdInfo idInfo;                                          \
            return idInfo;                                                 \
        }                                                                  \
        const char * getName() const override { return #name; }            \
        using Super = parentName


class Component
{
public:
    using Id = uint64_t;

    struct IdInfo
    {
        bool isId(Id id) const
        {
            return (id & m_idMask) == m_id;
        }

        Id getId() const { return m_id; }
        Id getMaskId() const { return m_idMask; }
        bool isRegistered() const { return m_idMask != 0; }
        void addChildren(IdInfo & _id);

    private:

        void buildIds(IdInfo & parent);
        void buildChildrenIds();

        Id m_id = 0;
        Id m_idMask = 0;
        vector<IdInfo*> m_children;
    };

    template <typename C>
    static void registerIdInfo();

    static void test();

    virtual const char * getName() const = 0;
};

template <typename C>
struct IdInfoOf
{
    static Component::IdInfo value;
};

template <typename C>
Component::IdInfo IdInfoOf<C>::value;


template <>
inline void Component::registerIdInfo<Component>() {}

template <typename C>
void Component::registerIdInfo()
{
    using Parent = C::Super;
    registerIdInfo<Parent>(); // recurse to ...

    auto & idInfo = IdInfoOf<C>::value;
    auto & superIdInfo = IdInfoOf<Parent>::value;
    superIdInfo.addChildren(idInfo);
}

#endif // COMPONENT_H_


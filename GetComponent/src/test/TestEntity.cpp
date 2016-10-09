#include "Entity.h"
#include "Component.h"



void Entity::test()
{
    Ensures(Entity{}.getComponent<Component>() == nullptr);
    // see test component
}



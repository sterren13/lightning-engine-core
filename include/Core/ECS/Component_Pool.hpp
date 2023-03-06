//
// Created by sterr on 5/03/2023.
//

#ifndef CORE_COMPONENT_POOL_HPP
#define CORE_COMPONENT_POOL_HPP
#include "Core/ECS/Entity_map.hpp"
#include "Core/Types.h"

namespace lightning::ECS {
    /*
     * Component_Pool holds all components of a type for all entities dat have that component
     */
    template<typename T>
    class Component_Pool {
    public:
        // check if entity has component
        bool Has(Entity_t entity) { return entity_data.contains(entity); }
        // add entity to pool
        void AddEntity(Entity_t entity) {
            entity_data.add(entity, T());
        }
        // set component for entity
        void Set(Entity_t entity, T data) {
            entity_data.get(entity) = data;
        }
        // get component for entity
        T& Get(Entity_t entity) {
            return entity_data.get(entity);
        }
    private:
        Entity_map<T> entity_data;
    };
} // ECS


#endif //CORE_COMPONENT_POOL_HPP

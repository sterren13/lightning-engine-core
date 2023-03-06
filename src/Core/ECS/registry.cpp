//
// Created by sterr on 5/03/2023.
//

#include <cassert>
#include "registry.h"

namespace lightning {
    namespace ECS {
        Entity_t registry::CreateEntity() {
            assert(NextEntity < MAX_ENTITIES); // TODO change to custom assert
            if (FreeEntitys.empty()){
                Entity_t new_entity = NextEntity;
                NextEntity++;
                EntitysSet.insert(new_entity);
                return new_entity;
            } else {
                Entity_t new_entity = FreeEntitys.back();
                FreeEntitys.pop_back();
                INCREASE_VERSION(new_entity);
                EntitysSet.insert(new_entity);
                return new_entity;
            }
        }

        void registry::DestroyEntity(Entity_t entity) {

        }

        bool registry::IsActive(Entity_t entity) {
            return EntitysSet.contains(entity);
        }
    } // lightning
} // ECS
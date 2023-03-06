//
// Created by sterr on 5/03/2023.
//

#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#include <cstdint>

namespace lightning {
    namespace ECS {
        #define MAX_ENTITIES 104856
        typedef uint32_t Entity_t;
        typedef uint32_t Entity_ID_t;
        typedef uint32_t Entity_Version_t;
        #define GET_ENTITY_ID(entity) (entity & 0xFFFFF)
        #define GET_ENTITY_VERSION(entity) (entity >> 20) & 0xFFF
        #define SET_ENTITY_VERSION(entity,version) id | (new_version << 20)
        #define INCREASE_VERSION(entity) entity += (1 << 20)
    } // ECS
}

#endif //CORE_TYPES_H

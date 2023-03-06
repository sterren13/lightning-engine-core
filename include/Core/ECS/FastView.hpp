//
// Created by sterr on 5/03/2023.
//

#ifndef CORE_FASTVIEW_HPP
#define CORE_FASTVIEW_HPP
#include <vector>
#include <tuple>
#include "Core/ECS/Component_Pool.hpp"

namespace lightning {
    namespace ECS {
        template<typename ... Ts>
        class FastView {
        public:
            
        private:
            std::vector<uint32_t> Entitys;
            std::tuple<Component_Pool<Ts>&...> ComponentPools;
            std::vector<std::vector<uint32_t>> Component_indexs;
        };
    } // lightning
} // ECS
#endif //CORE_FASTVIEW_HPP

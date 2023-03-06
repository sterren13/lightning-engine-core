//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_BASESYSTEM_H
#define CORE_BASESYSTEM_H
#include <utility>

#include "Core/Events/EventBus.hpp"
#include "Core/ECS/registry.h"
#include "Core/Base.h"

namespace lightning {

    class BaseSystem {
    public:
        ~BaseSystem() = default;
        virtual void OnInit() = 0;
        virtual void OnTick() = 0;

    protected:
        Ref<EventBus> eventBus;
        Ref<ECS::registry> registry;

    private:
        void Init(Ref<EventBus> in_eventBus, Ref<ECS::registry> in_registry) {
            eventBus = std::move(in_eventBus);
            registry = std::move(in_registry);
        }
    };

} // lightning

#endif //CORE_BASESYSTEM_H

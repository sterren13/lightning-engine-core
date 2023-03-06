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
        virtual void OnTick() = 0; // Called every frame
        void Init(Ref<EventBus> in_eventBus, Ref<ECS::registry> in_registry) {
            eventBus = std::move(in_eventBus);
            registry = std::move(in_registry);
            OnInit();
        }

    protected:
        virtual void OnInit() = 0; // Called when the engine is initialized

    protected:
        Ref<EventBus> eventBus;
        Ref<ECS::registry> registry;
    };

} // lightning

#endif //CORE_BASESYSTEM_H

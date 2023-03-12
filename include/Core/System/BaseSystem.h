//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_BASESYSTEM_H
#define CORE_BASESYSTEM_H
#include <utility>

#include "Core/Events/EventManager.hpp"
#include "Core/ECS/registry.h"
#include "Core/Base.h"

namespace lightning {

    class BaseSystem {
    public:
        ~BaseSystem() = default;
        virtual const char* GetName() const = 0;
        virtual void OnTick() = 0; // Called every frame
        void Init(Ref<EventManager> in_eventManager, Ref<ECS::registry> in_registry) {
            eventManager = std::move(in_eventManager);
            registry = std::move(in_registry);
            OnInit();
        }

    protected:
        virtual void OnInit() = 0; // Called when the engine is initialized

    protected:
        Ref<EventManager> eventManager;
        Ref<ECS::registry> registry;
    };

} // lightning

#endif //CORE_BASESYSTEM_H

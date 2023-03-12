//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_SYSTEMMANGER_H
#define CORE_SYSTEMMANGER_H
#include "Core/Base.h"
#include "BaseSystem.h"
#include <unordered_map>
#include <vector>

namespace lightning {
    class SystemManger {
    public:
        ~SystemManger();
        void AddSystem(BaseSystem* system, size_t priority, bool enabled = false);
        void RemoveSystem(const char* name);
        void EnableSystem(const char* name);
        void DisableSystem(const char* name);
        bool GetSystemState(const char* name);
        bool DusSystemExist(const char* name);

        void OnInit(Ref<EventManager> in_eventManager, Ref<ECS::registry> in_registry);
        void OnTick();
    private:
        struct SystemCharateristics {
            size_t priority;
            bool enabled;
            BaseSystem* system;
        };
        std::vector<SystemCharateristics> m_systems;
        std::unordered_map<const char*, size_t> m_systemMap;
    };
} // lightning

#endif //CORE_SYSTEMMANGER_H

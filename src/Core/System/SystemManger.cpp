//
// Created by sterr on 6/03/2023.
//

#include "Core/System/SystemManger.h"

#include <algorithm>
#include "Core/Log/Loger.h"

namespace lightning{

    SystemManger::~SystemManger() {
        for (auto& system : m_systems) {
            delete system.system;
        }
    }

    void SystemManger::AddSystem(BaseSystem *system, size_t priority, bool enabled) {
        LIGHTNING_ASSERT(!DusSystemExist(system->GetName()), "System already exist");
        m_systems.push_back({priority,enabled, system});
        m_systemMap.insert({system->GetName(), m_systems.size() - 1});
        std::sort(m_systems.begin(), m_systems.end(), [](const SystemCharateristics& a, const SystemCharateristics& b) {
            return a.priority < b.priority;
        });
    }

    void SystemManger::RemoveSystem(const char *name) {
        LIGHTNING_ASSERT(DusSystemExist(name), "System does not exist");
        m_systems.erase(m_systems.begin() + m_systemMap[name]);
        m_systemMap.erase(name);
    }

    void SystemManger::EnableSystem(const char *name) {
        LIGHTNING_ASSERT(DusSystemExist(name), "System does not exist");
        m_systems[m_systemMap[name]].enabled = true;
    }

    void SystemManger::DisableSystem(const char *name) {
        LIGHTNING_ASSERT(DusSystemExist(name), "System does not exist");
        m_systems[m_systemMap[name]].enabled = false;
    }

    bool SystemManger::GetSystemState(const char *name) {
        LIGHTNING_ASSERT(DusSystemExist(name), "System does not exist");
        return m_systems[m_systemMap[name]].enabled;
    }

    bool SystemManger::DusSystemExist(const char *name) {
        return m_systemMap.find(name) != m_systemMap.end();
    }

    void SystemManger::OnInit(Ref<EventBus> in_eventBus, Ref<ECS::registry> in_registry) {
        for (auto& system : m_systems) {
            system.system->Init(in_eventBus, in_registry);
        }
    }

    void SystemManger::OnTick() {
        for (auto& system : m_systems) {
            if (system.enabled) {
                system.system->OnTick();
            }
        }
    }
}
//
// Created by sterr on 6/03/2023.
//

#include "SystemManger.h"
#include "Core/Log/Loger.h"

namespace lightning{

    SystemManger::~SystemManger() {
        for (auto& system : m_systems) {
            delete system.second;
        }
    }

    void SystemManger::AddSystem(const char *name, BaseSystem *system, bool enabled) {
        LIGHTNING_ASSERT(!DusSystemExist(name), "System already exist");
        m_systems.push_back({enabled, system});
        m_systemMap.insert({name, m_systems.size() - 1});
    }

    void SystemManger::RemoveSystem(const char *name) {
        LIGHTNING_ASSERT(DusSystemExist(name), "System does not exist");
        m_systems.erase(m_systems.begin() + m_systemMap[name]);
        m_systemMap.erase(name);
    }

    void SystemManger::EnableSystem(const char *name) {
        LIGHTNING_ASSERT(DusSystemExist(name), "System does not exist");
        m_systems[m_systemMap[name]].first = true;
    }

    void SystemManger::DisableSystem(const char *name) {
        LIGHTNING_ASSERT(DusSystemExist(name), "System does not exist");
        m_systems[m_systemMap[name]].first = false;
    }

    bool SystemManger::GetSystemState(const char *name) {
        LIGHTNING_ASSERT(DusSystemExist(name), "System does not exist");
        return m_systems[m_systemMap[name]].first;
    }

    bool SystemManger::DusSystemExist(const char *name) {
        return m_systemMap.find(name) != m_systemMap.end();
    }

    void SystemManger::OnInit(Ref<EventBus> in_eventBus, Ref<ECS::registry> in_registry) {
        for (auto& system : m_systems) {
            system.second->Init(in_eventBus, in_registry);
        }
    }

    void SystemManger::OnTick() {
        for (auto& system : m_systems) {
            if (system.first) {
                system.second->OnTick();
            }
        }
    }
}
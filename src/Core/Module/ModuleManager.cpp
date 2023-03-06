//
// Created by sterr on 6/03/2023.
//

#include "Core/Module/ModuleManager.h"
#include "Core/Log/Loger.h"

namespace lightning {
    ModuleManager &lightning::ModuleManager::get() {
        static ModuleManager instance;
        return instance;
    }

    void ModuleManager::LoadModule(const char *moduleName, BaseModule * basemodule) {
        LIGHTNING_ASSERT(m_ModuleMap.find(moduleName) == m_ModuleMap.end(), "Module already loaded");
        m_ModuleMap.insert({moduleName, m_Modules.size()});
        m_Modules.emplace_back(basemodule);
        LIGHTNING_LOG_INFO_DEBUG("Module Loaded: ", moduleName);
    }

    void ModuleManager::UnloadModule(const char *moduleName) {
        LIGHTNING_ASSERT(m_ModuleMap.find(moduleName) != m_ModuleMap.end(), "Module not loaded");
        m_Modules.erase(m_Modules.begin() + m_ModuleMap[moduleName]);
        m_ModuleMap.erase(moduleName);
        LIGHTNING_LOG_INFO_DEBUG("Module Unloaded: ", moduleName);
    }

    void ModuleManager::ActivateModule(const char *moduleName) {
        LIGHTNING_ASSERT(m_ModuleMap.find(moduleName) != m_ModuleMap.end(), "Module not loaded");
        m_Modules[m_ModuleMap[moduleName]]->Activate();
        LIGHTNING_LOG_INFO_DEBUG("Module Activated: ", moduleName);
    }

    void ModuleManager::DeactivateModule(const char *moduleName) {
        LIGHTNING_ASSERT(m_ModuleMap.find(moduleName) != m_ModuleMap.end(), "Module not loaded");
        m_Modules[m_ModuleMap[moduleName]]->Deactivate();
        LIGHTNING_LOG_INFO_DEBUG("Module Deactivated: ", moduleName);
    }

    bool ModuleManager::IsModuleActive(const char *moduleName) {
        LIGHTNING_ASSERT(m_ModuleMap.find(moduleName) != m_ModuleMap.end(), "Module not loaded");
        return m_Modules[m_ModuleMap[moduleName]]->IsActivated();
    }
} // lightning
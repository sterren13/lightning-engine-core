//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_MODULEMANAGER_H
#define CORE_MODULEMANAGER_H
#include "BaseModule.h"

#include <vector>
#include <unordered_map>

namespace lightning {

    class ModuleManager {
    public:
        static ModuleManager& get();
        void LoadModule(const char* moduleName, BaseModule* module);
        void UnloadModule(const char* moduleName);
        void ActivateModule(const char* moduleName);
        void DeactivateModule(const char* moduleName);
        bool IsModuleActive(const char* moduleName);
        inline std::vector<BaseModule*>& Each() { return m_Modules; }
    private:
        std::vector<BaseModule*> m_Modules;
        std::unordered_map<const char*, size_t> m_ModuleMap;
    };
} // lightning

#endif //CORE_MODULEMANAGER_H

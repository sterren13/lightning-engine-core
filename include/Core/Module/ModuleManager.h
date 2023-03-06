//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_MODULEMANAGER_H
#define CORE_MODULEMANAGER_H
#include "BaseModule.h"

#include <vector>
#include <unordered_map>

namespace lightning {
    /*
     * ModuleManager is a singleton class that manages all modules in the engine.
     */
    class ModuleManager {
    public:
        static ModuleManager& get(); // get singleton instance
        void LoadModule(const char* moduleName, BaseModule* module); // load a module
        void UnloadModule(const char* moduleName); // unload a module by name
        void ActivateModule(const char* moduleName); // activate a module by name
        void DeactivateModule(const char* moduleName); // deactivate a module by name
        bool IsModuleActive(const char* moduleName); // check if a module is active
        inline std::vector<BaseModule*>& Each() { return m_Modules; } // iterator for all modules
    private:
        std::vector<BaseModule*> m_Modules;
        std::unordered_map<const char*, size_t> m_ModuleMap;
    };
} // lightning

#endif //CORE_MODULEMANAGER_H

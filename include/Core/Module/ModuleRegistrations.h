//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_MODULEREGISTRATIONS_H
#define CORE_MODULEREGISTRATIONS_H
#include "ModuleManager.h"

// This is a macro that is used to register a module with the module manager when the module is statically linked.
#define DIF_MODULE(Name, Type) namespace lightning::ModuleRegistration {ModeuleRegistration<Type> Name(Name);}

namespace lightning{
    namespace ModuleRegistrations {
        template<typename T>
        class ModuleRegistration {
        public:
            ModuleRegistration(const char *ModuleName) {
                ModuleManager::get().LoadModule(ModuleName, new T);
            }
        };
    }
}

#endif //CORE_MODULEREGISTRATIONS_H

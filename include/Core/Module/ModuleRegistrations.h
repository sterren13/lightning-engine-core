//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_MODULEREGISTRATIONS_H
#define CORE_MODULEREGISTRATIONS_H
#include "ModuleManager.h"

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

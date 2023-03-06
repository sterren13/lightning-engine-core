//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_BASEMODULE_H
#define CORE_BASEMODULE_H
#include <string>

namespace lightning {
    /*
     * BaseModule is the base class for all modules in the engine.*
     * OnInit is called when the module is initialized.
     * OnReload is called when the module is reloaded.
     * OnActivate is called when the module is activated.
     * OnDeactivate is called when the module is deactivated.
     * OnShutdown is called when the application is shutting down.
     * All functions must be overridden by the derived class.
     */
    class BaseModule {
    public:
        // virtual functions
        virtual const char* GetName() = 0; // return the name of the module
        virtual void OnInit() = 0; // called when the module is initialized
        virtual void OnReload() = 0; // called when the module is reloaded
        virtual void OnActivate() = 0; // called when the module is activated
        virtual void OnDeactivate() = 0; // called when the module is deactivated
        virtual void OnShutdown() = 0; // called when the application is shutting down
        virtual ~BaseModule() = default;

        // module management functions
        inline bool IsActivated() const { return Active; } // check if the module is activated
        // activate the module
        inline void Activate() {
            Active = true; OnActivate();
            OnActivate();
        }
        // deactivate the module
        inline void Deactivate() {
            Active = false; OnDeactivate();
            OnDeactivate();
        }
    private:
        bool Active = false;
    };

} // lightning

#endif //CORE_BASEMODULE_H

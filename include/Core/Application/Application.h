//
// Created by Arno Joosen on 5/03/2023.
//

#ifndef LIGHTNING_ENGINE_CORE_APPLICATION_H
#define LIGHTNING_ENGINE_CORE_APPLICATION_H
#include "Core/Events/EventBus.hpp"
#include "Core/Base.h"

namespace lightning {
    /*
     * The Application class is the main class of the engine.
     * It is responsible for the main loop and the initialization of the engine.
     */
    class Application {
    private:
        Application();
        void Run(); // main loop of the engine
        void OnInit(); // initialize the engine
        void OnTick(); // tick the engine
        void OnPause(); // pause the engine
        void OnResume(); // resume the engine
        void OnExit(); // exit the engine

        // event callbacks functions
        void OnPauseEvent();
        void OnResumeEvent();
        void OnExitEvent();
    private:
        Ref<EventBus> eventBus;
        bool paused = false;
        bool wantsToExit = false;
    };
} // lightning

#endif //LIGHTNING_ENGINE_CORE_APPLICATION_H

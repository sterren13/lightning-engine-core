//
// Created by Arno Joosen on 5/03/2023.
//

#ifndef LIGHTNING_ENGINE_CORE_APPLICATION_H
#define LIGHTNING_ENGINE_CORE_APPLICATION_H
#include "Core/Events/EventManager.hpp"
#include "Core/Window/Window.h"
#include "Core/System/SystemManger.h"
#include "Core/Module/ModuleManager.h"
#include "Core/ECS/registry.h"
#include "Core/Base.h"
#include "Core/Time/Timer.h"

namespace lightning {
    /*
     * The ApplicationConfig struct is used to configure the application.
     */
    struct ApplicationConfig {
        std::string name; // name of the application
        uint32_t width; // width of the window
        uint32_t height; // height of the window
        bool fullscreen = false; // fullscreen mode
        bool vsync = true; // vsync mode
        float TickTime = 1.0f / 60.0f; // tick time
        GraphicsAPI graphicsAPI = GraphicsAPI::OpenGL; // graphics API
    };
    /*
     * The Application class is the main class of the engine.
     * It is responsible for the main loop and the initialization of the engine.
     */
    class Application {
    public:
        Application(ApplicationConfig config);
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

        // getters
        Window& GetWindow() { return *window; }
        EventManager& GetEventManager() { return *eventManager; }
        ECS::registry& GetRegistry() { return *registry; }
        SystemManger& GetSystemManager() { return *systemManager; }
        ModuleManager& GetModuleManager() { return *moduleManager; }
    private:
        Ref<Window> window;
        Ref<EventManager> eventManager;
        Ref<ECS::registry> registry;
        Ref<SystemManger> systemManager;
        Ref<ModuleManager> moduleManager;
        bool paused = false;
        bool wantsToExit = false;
        ApplicationConfig m_config;
        Timer FixedTickTimer;
    };
} // lightning

#endif //LIGHTNING_ENGINE_CORE_APPLICATION_H

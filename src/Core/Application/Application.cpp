//
// Created by sterr on 5/03/2023.
//

#include "Core/Application/Application.h"

namespace lightning {

    Application::Application(ApplicationConfig config) :
            eventBus(CreateRef<EventBus>()),
            registry(CreateRef<ECS::registry>()),
            m_config(config),
            systemManager(CreateRef<SystemManger>()){
    }

    void Application::Run() {
        OnInit();
        FixedTickTimer.Reset();
        while (!wantsToExit) {
            eventBus->ProcessEvents();
            OnTick();
            if (FixedTickTimer.GetCurrentTimeMicro() >= m_config.TickTime) {
                FixedTickTimer.Reset();
                eventBus->PushEvent("FixedTick");
            }
        }
        OnExit();
    }

    void Application::OnInit() {
        // register events and listeners
        eventBus->RegisterEvent("Exit");
        eventBus->RegisterListener("Exit", ENGINE_BIND_EVENT_FN(Application::OnExitEvent));
        eventBus->RegisterEvent("Pause");
        eventBus->RegisterListener("Pause", ENGINE_BIND_EVENT_FN(Application::OnPauseEvent));
        eventBus->RegisterEvent("Resume");
        eventBus->RegisterListener("Resume", ENGINE_BIND_EVENT_FN(Application::OnResumeEvent));
        eventBus->RegisterEvent("FixedTick");

        // create window
        window = Window::Create(m_config.name.c_str(), m_config.width, m_config.height, m_config.fullscreen, m_config.vsync, m_config.graphicsAPI);
        window->SetEventCallbacks(*eventBus);

        // load modules
        for (auto& system : ModuleManager::get().Each()){
            system->OnInit();
        }
        systemManager->OnInit(eventBus, registry);
    }

    void Application::OnTick() {
        window->Update();
        systemManager->OnTick();
    }

    void Application::OnPause() {

    }

    void Application::OnResume() {

    }

    void Application::OnExit() {
        for (auto& system : ModuleManager::get().Each()){
            system->OnShutdown();
        }
    }

    void Application::OnPauseEvent() {
        paused = true;
        LIGHTNING_LOG_EVENT("Pausing...");
        OnPause();
    }

    void Application::OnResumeEvent() {
        paused = false;
        LIGHTNING_LOG_EVENT("Resuming...");
        OnResume();
    }

    void Application::OnExitEvent() {
        wantsToExit = true;
        LIGHTNING_LOG_EVENT("Exiting...");
    }
} // lightning

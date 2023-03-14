//
// Created by sterr on 5/03/2023.
//

#include "Core/Application/Application.h"

namespace lightning {

    Application::Application(ApplicationConfig config) :
            eventManager(CreateRef<EventManager>()),
            registry(CreateRef<ECS::registry>()),
            m_config(config),
            systemManager(CreateRef<SystemManger>()){
    }

    void Application::Run() {
        OnInit();
        FixedTickTimer.Reset();
        while (!wantsToExit) {
            eventManager->ProcessEvents();
            OnTick();
            if (FixedTickTimer.GetCurrentTimeMicro() >= m_config.TickTime) {
                FixedTickTimer.Reset();
                eventManager->PushEvent("FixedTick");
            }
        }
        OnExit();
    }

    void Application::OnInit() {
        // register events and m_listeners
        eventManager->RegisterEvent("Exit");
        eventManager->RegisterListener("Exit", ENGINE_BIND_EVENT_FN(Application::OnExitEvent));
        eventManager->RegisterEvent("Pause");
        eventManager->RegisterListener("Pause", ENGINE_BIND_EVENT_FN(Application::OnPauseEvent));
        eventManager->RegisterEvent("Resume");
        eventManager->RegisterListener("Resume", ENGINE_BIND_EVENT_FN(Application::OnResumeEvent));
        eventManager->RegisterEvent("FixedTick");

        // create window
        window = Window::Create(m_config.name.c_str(), m_config.width, m_config.height, m_config.fullscreen, m_config.vsync, m_config.graphicsAPI);
        window->SetEventCallbacks(*eventManager);

        // load modules
        for (auto& system : ModuleManager::get().Each()){
            system->OnInit();
        }
        systemManager->OnInit(eventManager, registry);
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

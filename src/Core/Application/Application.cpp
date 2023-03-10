//
// Created by sterr on 5/03/2023.
//

#include "Core/Application/Application.h"

namespace lightning {

    Application::Application() : eventBus(CreateRef<EventBus>()), registry(CreateRef<ECS::registry>()) {
    }

    void Application::Run() {
        OnInit();
        while (!wantsToExit) {
            eventBus->ProcessEvents();
            OnTick();
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

        // create window
        window = Window::Create("Lightning Engine", 1280, 720);
        window->SetEventCallbacks(*eventBus);

        // create system manager and load modules and systems
        systemManager = CreateRef<SystemManger>();
        for (auto& system : ModuleManager::get().Each()){
            system->OnInit();
        }
        systemManager->OnInit(eventBus, registry);
    }

    void Application::OnTick() {
        window->Update();
    }

    void Application::OnPause() {

    }

    void Application::OnResume() {

    }

    void Application::OnExit() {

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
        LIGHTNING_LOG_EVENT("Exiting...");
        wantsToExit = true;
    }
} // lightning

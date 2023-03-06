//
// Created by sterr on 5/03/2023.
//

#include "Core/Application/Application.h"

namespace lightning {

    Application::Application() : eventBus(CreateRef<EventBus>()) {

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
        eventBus->RegisterEvent("Pause");
        eventBus->RegisterListener("Pause", ENGINE_BIND_EVENT_FN(Application::OnPauseEvent));
        eventBus->RegisterEvent("Resume");
        eventBus->RegisterListener("Resume", ENGINE_BIND_EVENT_FN(Application::OnResumeEvent));
        eventBus->RegisterEvent("Exit");
        eventBus->RegisterListener("Exit", ENGINE_BIND_EVENT_FN(Application::OnExit));
    }

    void Application::OnTick() {

    }

    void Application::OnPause() {

    }

    void Application::OnResume() {

    }

    void Application::OnExit() {

    }

    void Application::OnPauseEvent() {
        paused = true;
        OnPause();
    }

    void Application::OnResumeEvent() {
        paused = false;
        OnResume();
    }

    void Application::OnExitEvent() {
        wantsToExit = true;
    }
} // lightning

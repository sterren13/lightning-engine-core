//
// Created by Arno Joosen on 5/03/2023.
//

#ifndef LIGHTNING_ENGINE_CORE_APPLICATION_H
#define LIGHTNING_ENGINE_CORE_APPLICATION_H
namespace lightning {
    /*
     * The Application class is the main class of the engine.
     * It is responsible for the main loop and the initialization of the engine.
     */
    class Application {
    private:
        Application() = default;
        void Run(); // main loop of the engine
        void OnInit(); // initialize the engine
        void OnTick(); // tick the engine
        void OnPause(); // pause the engine
        void OnResume(); // resume the engine
        void OnExit(); // exit the engine

        // change state of the engine
        inline void Exit() { wantsToExit = true; }
        [[nodiscard]] inline bool WantsToExit() const {return wantsToExit;} // check if the engine wants to exit
        inline void pause() { paused = true; } // pause the engine
        inline void resume() { paused = false; } // resume the engine
        [[nodiscard]] inline bool isPaused() const { return paused; } // check if the engine is paused
    private:
        bool paused = false;
        bool wantsToExit = false;
    };
} // lightning

#endif //LIGHTNING_ENGINE_CORE_APPLICATION_H

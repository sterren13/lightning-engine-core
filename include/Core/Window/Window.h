//
// Created by sterr on 7/03/2023.
//

#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include <cstddef>
#include "Core/Base.h"
#include "Core/Window/Window_Events.h"
#include "Core/Events/EventBus.hpp"

namespace lightning {

    enum class GraphicsAPI {
        OpenGL = 0,
        Vulkan = 1,
        Metal = 2
    };

    class Window {
    public:
        ~Window() = default;

        virtual void Update()= 0;
        virtual void SetTitle(const char* title) = 0;
        virtual void SetEventCallbacks(EventBus& eventBus) = 0;

        // window properties
        virtual const size_t GetWidth() const = 0;
        virtual const size_t GetHeight() const = 0;
        virtual bool IsFullScreen() const = 0;
        virtual bool IsVSync() const = 0;

        // set window properties
        virtual void SetDimensions(size_t width, size_t height) = 0;
        virtual void SetFullScreen(bool fullscreen) = 0;
        virtual void SetVSync(bool vsync) = 0;

        static Ref<Window> Create(const char* title, size_t width, size_t height, bool fullscreen, bool vsync, GraphicsAPI api = GraphicsAPI::OpenGL);
    };

} // lightning

#endif //CORE_WINDOW_H

//
// Created by sterr on 7/03/2023.
//

#include "Core/Window/Window.h"
#include "../../Platform/OpenGL/OpenGL_Window.h"

namespace lightning {
    Ref<Window> Window::Create(const char* title, size_t width, size_t height, bool fullscreen, bool vsync, GraphicsAPI api) {
        if (api == GraphicsAPI::OpenGL)
            return CreateRef<Platform::OpenGL_Window>(title, width, height, fullscreen, vsync);
        return nullptr;
    }
} // lightning
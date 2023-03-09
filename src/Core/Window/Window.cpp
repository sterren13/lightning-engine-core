//
// Created by sterr on 7/03/2023.
//

#include "Core/Window/Window.h"
#include "../../Platform/OpenGL/OpenGL_Window.h"

namespace lightning {
    Ref<Window> Window::Create(const char *title, size_t width, size_t height, GraphicsAPI api) {
        return CreateRef<Platform::OpenGL_Window>(title, width, height);
    }
} // lightning
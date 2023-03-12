//
// Created by sterr on 7/03/2023.
//

#ifndef CORE_OPENGL_WINDOW_H
#define CORE_OPENGL_WINDOW_H
#include "GLFW/glfw3.h"
#include "Core/Window/Window.h"

namespace lightning {
    namespace Platform {

        class OpenGL_Window : public Window {
        public:
            OpenGL_Window(const char* title, uint32_t width, uint32_t height, bool fullscreen = false, bool vsync = true);
            ~OpenGL_Window();

            void Update() override;
            void SetTitle(const char* title) override;
            void SetEventCallbacks(EventManager& eventManager) override;

            // window properties
            const size_t GetWidth() const override;
            const size_t GetHeight() const override;
            bool IsFullScreen() const override;
            bool IsVSync() const override;

            // set window properties
            void SetDimensions(size_t width, size_t height) override;
            void SetFullScreen(bool fullscreen) override;
            void SetVSync(bool vsync) override;

        private:

            static void GLFW_ErrorCallback(int error, const char* description);
            static void GLFW_ResizedCallback(GLFWwindow* window, int width, int height);
            static void GLFW_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void GLFW_MouseButtonCallback(GLFWwindow *wnd, int button, int state, int mods);
            static void GLFW_CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
            static void GLFW_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
            static void GLFW_CharCallback(GLFWwindow* window, unsigned int codepoint);
            static void GLFW_JoystickCallback(int joy, int event);

            void _CreateWindow(const char* title, uint32_t width, uint32_t height);
        private:
            EventManager* m_EventManager = nullptr;
            GLFWwindow* m_Window;
            bool m_FullScreen, m_VSync;
        };

    } // lightning
} // Platform

#endif //CORE_OPENGL_WINDOW_H

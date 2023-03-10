//
// Created by sterr on 7/03/2023.
//

#include "OpenGL_Window.h"
#include "Core/Log/Loger.h"

namespace lightning {
    namespace Platform {
        OpenGL_Window::OpenGL_Window(const char *title, uint32_t width, uint32_t height, bool fullscreen, bool vsync) :
            m_FullScreen(fullscreen), m_VSync(vsync) {
            _CreateWindow(title, width, height);
        }

        OpenGL_Window::~OpenGL_Window() {
            if (m_Window)
                glfwDestroyWindow(m_Window);
            glfwTerminate();
        }

        void OpenGL_Window::Update() {
            glfwSwapBuffers(m_Window);
            glfwPollEvents();
            if(glfwWindowShouldClose(m_Window))
                m_EventBus->PushEvent("Exit");
        }

        void OpenGL_Window::SetTitle(const char *title) {
            glfwSetWindowTitle(m_Window, title);
        }

        void OpenGL_Window::SetEventCallbacks(EventBus& eventBus) {
            glfwSetWindowUserPointer(m_Window, &eventBus);

            // keyboard
            eventBus.RegisterEvent<KeyPressedEvent>();
            eventBus.RegisterEvent<KeyRepeatEvent>();
            eventBus.RegisterEvent<KeyReleasedEvent>();
            glfwSetKeyCallback(m_Window, GLFW_KeyCallback);

            // mouse
            //eventBus.RegisterEvent<MouseButtonPressedEvent>();
            //eventBus.RegisterEvent<MouseButtonRepeatEvent>();
            //eventBus.RegisterEvent<MouseButtonReleasedEvent>();
            //glfwSetMouseButtonCallback(m_Window, GLFW_MouseButtonCallback);
//
            //eventBus.RegisterEvent<MouseMovedEvent>();
            //glfwSetCursorPosCallback(m_Window, GLFW_CursorPositionCallback);
//
            //eventBus.RegisterEvent<MouseScrolledEvent>();
            //glfwSetScrollCallback(m_Window, GLFW_ScrollCallback);

            // window
            eventBus.RegisterEvent<WindowResizedEvent>();
            glfwSetWindowSizeCallback(m_Window, GLFW_ResizedCallback);
            m_EventBus = &eventBus;
        }

        const size_t OpenGL_Window::GetWidth() const {
            int width, height;
            glfwGetWindowSize(m_Window, &width, &height);
            return width;
        }

        const size_t OpenGL_Window::GetHeight() const {
            int width, height;
            glfwGetWindowSize(m_Window, &width, &height);
            return height;
        }

        bool OpenGL_Window::IsFullScreen() const {
            return m_FullScreen;
        }

        bool OpenGL_Window::IsVSync() const {
            return m_VSync;
        }

        void OpenGL_Window::SetDimensions(size_t width, size_t height) {
            glfwSetWindowSize(m_Window, width, height);
        }

        void OpenGL_Window::SetFullScreen(bool fullscreen) {
            m_FullScreen = fullscreen;
            if (m_FullScreen) {
                GLFWmonitor *monitor = glfwGetWindowMonitor(m_Window);
                const GLFWvidmode *mode = glfwGetVideoMode(monitor);
                glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            }
        }

        void OpenGL_Window::SetVSync(bool vsync) {
            m_VSync = vsync;
            if (m_VSync) {
                glfwSwapInterval(1);
            } else {
                glfwSwapInterval(0);
            }
        }

        void OpenGL_Window::_CreateWindow(const char *title, size_t width, size_t height) {
            LIGHTNING_ASSERT(glfwInit(), "Window already created");


            // set opengl settings
            glfwWindowHint(GLFW_SAMPLES, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // create window
            m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);

            // check if window is created
            LIGHTNING_ASSERT(m_Window, "window not valid");

            // make window context current
            glfwMakeContextCurrent(m_Window);

            // set fullscreenglfwCreateWindow(width, height, title, nullptr, nullptr);
            if (m_FullScreen) {
                GLFWmonitor *monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode *mode = glfwGetVideoMode(monitor);
                glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            }

            // set vsync
            if (m_VSync) {
                glfwSwapInterval(1);
            } else {
                glfwSwapInterval(0);
            }
        }

        void OpenGL_Window::GLFW_ErrorCallback(int error, const char *description) {
            LIGHTNING_LOG_ERROR("GLFW Error ({0}): {1}", error, description);
        }

        void OpenGL_Window::GLFW_ResizedCallback(GLFWwindow *window, int width, int height) {
            void* data = glfwGetWindowUserPointer(window);
            EventBus* eventBus = static_cast<EventBus*>(data);
            eventBus->PushEvent<WindowResizedEvent>({width, height});
        }

        void OpenGL_Window::GLFW_KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
            void* data = glfwGetWindowUserPointer(window);
            EventBus* eventBus = static_cast<EventBus*>(data);
            Keyboard::Code code = key;
            switch (action) {
                case GLFW_PRESS: {
                    eventBus->PushEvent<KeyPressedEvent>({code});
                    break;
                }
                case GLFW_RELEASE: {
                    eventBus->PushEvent<KeyReleasedEvent>({code});
                    break;
                }
                case GLFW_REPEAT: {
                    eventBus->PushEvent<KeyPressedEvent>({code});
                    break;
                }
            }
        }

        void OpenGL_Window::GLFW_MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
            void* data = glfwGetWindowUserPointer(window);
            EventBus* eventBus = static_cast<EventBus*>(data);
            Mouse::Code code = button;
            switch (action) {
                case GLFW_RELEASE: // The mouse button was released.
                    eventBus->PushEvent<MouseButtonReleasedEvent>({code});
                    break;
                case GLFW_PRESS: // The mouse button was pressed.
                    eventBus->PushEvent<MouseButtonPressedEvent>({code});
                    break;
                case GLFW_REPEAT: // The mouse button was held down until it repeated.
                    eventBus->PushEvent<MouseButtonReleasedEvent>({code});
                    break;
                default:
                    break;
            }

        }

        void OpenGL_Window::GLFW_CursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
            void* data = glfwGetWindowUserPointer(window);
            EventBus* eventBus = static_cast<EventBus*>(data);
            eventBus->PushEvent<MouseMovedEvent>({xpos, ypos});
        }

        void OpenGL_Window::GLFW_ScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
            void* data = glfwGetWindowUserPointer(window);
            EventBus* eventBus = static_cast<EventBus*>(data);
            eventBus->PushEvent<MouseScrolledEvent>({xoffset, yoffset});
        }

        void OpenGL_Window::GLFW_CharCallback(GLFWwindow *window, unsigned int codepoint) {
            // TODO implement char callback with event bus
        }

        void OpenGL_Window::GLFW_JoystickCallback(int joy, int event) {
            // TODO implement joystick callback with event bus
        }
    } // Platform
} // lightning
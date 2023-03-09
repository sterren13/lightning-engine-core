//
// Created by arno on 9/03/23.
//

#ifndef CORE_WINDOW_EVENTS_H
#define CORE_WINDOW_EVENTS_H

#include "Core/IO/KeyCode.h"
#include "Core/IO/MouseCode.h"

namespace lightning{
    // keyboard events
    struct KeyPressedEvent {
        Keyboard::Code keycode;
    };

    struct KeyRepeatEvent {
        Keyboard::Code keycode;
    };

    struct KeyReleasedEvent {
        Keyboard::Code keycode;
    };

    // mouse events
    struct MouseMovedEvent {
        double x, y;
    };
    struct MouseScrolledEvent {
        double xOffset, yOffset;
    };

    struct MouseButtonPressedEvent {
        Mouse::Code button;
    };

    struct MouseButtonReleasedEvent {
        Mouse::Code button;
    };

    struct MouseButtonRepeatEvent {
        Mouse::Code button;
    };

    // window events
    struct WindowResizedEvent {
        int width, height;
    };

    // TODO joystick events
} // lightning

#endif //CORE_WINDOW_EVENTS_H

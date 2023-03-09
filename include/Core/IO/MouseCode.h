//
// Created by arno on 9/03/23.
//

#ifndef CORE_MOUSECODE_H
#define CORE_MOUSECODE_H

#include <cstdint>

namespace lightning::Mouse {
    using Code = uint16_t;
    enum : Code {
        // From glfw3.h
        Button0                = 0,
        Button1                = 1,
        Button2                = 2,
        Button3                = 3,
        Button4                = 4,
        Button5                = 5,
        Button6                = 6,
        Button7                = 7,

        ButtonLast             = Button7,
        ButtonLeft             = Button0,
        ButtonRight            = Button1,
        ButtonMiddle           = Button2
    };

} // lightning::Mouse
#endif //CORE_MOUSECODE_H

//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_WINDOW_LOG_H
#define CORE_WINDOW_LOG_H
#ifdef _WIN32
#include <windows.h>
#include <iostream>
#endif

#ifndef LIGHTNING_ENGINE_CORE_WINDOW_LOG_H
#define LIGHTNING_ENGINE_CORE_WINDOW_LOG_H

namespace lightning {
#ifdef _WIN32

    // Set the console text color to blue for Windows
    inline std::ostream &blue(std::ostream &s) {
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        return s;
    }

    // Set the console text color to red for windows
    inline std::ostream &red(std::ostream &s) {
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
        return s;
    }

    // Set the console text color to green for windows
    inline std::ostream &green(std::ostream &s) {
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        return s;
    }

    // Set the console text color to yellow for windows
    inline std::ostream &yellow(std::ostream &s) {
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        return s;
    }

    // Set the console text color to white for windows
    inline std::ostream &white(std::ostream &s) {
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        return s;
    }

    struct color {
        color(WORD attribute) : m_color(attribute) {};
        WORD m_color;
    };

    template<class _Elem, class _Traits>
    std::basic_ostream<_Elem, _Traits> &
    operator<<(std::basic_ostream<_Elem, _Traits> &i, color &c) {
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdout, c.m_color);
        return i;
    }

#define NC white // default white color
#define RED red // default red color
#define GRN green // default green color
#define YEL yellow // default yellow color
#define CYN blue // default blue color
#endif
#endif //LIGHTNING_ENGINE_CORE_WINDOW_LOG_H
} // lightning

#endif //CORE_WINDOW_LOG_H

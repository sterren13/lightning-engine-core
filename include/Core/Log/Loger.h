//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_LOGER_H
#define CORE_LOGER_H
#include <iostream>
#include <cassert>
#include "Platform/Linux/Linux_Log.h"
#include "Platform/OSX/OSX_Log.h"
#include "Platform/Windows/Window_Log.h"

#define DEBUG

namespace lightning {

    enum LogType {
        Info,
        Warning,
        Error,
        Event
    };
    template<class... Args>
    void Log(LogType Type, Args... args){
        switch (Type) {
            case LogType::Info:
                std::cout << GRN << "[Info] ";
                break;
            case LogType::Warning:
                std::cout << YEL << "[Warning] ";
                break;
            case LogType::Error:
                std::cout << RED << "[Error] ";
                break;
            case LogType::Event:
                std::cout << CYN << "[Event] ";
                break;
            default:
                std::cout << RED << "[No Type] ";
        }
        (std::cout << ... << args) << "\n" << NC;
    }

    template<class... Args>
    void Log_Debug(LogType Type, const char* at, Args... args){
#ifdef DEBUG
        switch (Type) {
            case LogType::Info:
                std::cout << GRN << "[Info] ";
                break;
            case LogType::Warning:
                std::cout << YEL << "[Warning] ";
                break;
            case LogType::Error:
                std::cout << RED << "[Error] ";
                break;
            case LogType::Event:
                std::cout << CYN << "[Event] ";
                break;
            default:
                std::cout << RED << "[No Type] ";
        }
        (std::cout << ... << args) << NC << " " << at << "\n";
#endif // DEBUG
    }


} // lightning

// logger
#define LIGHTNING_LOG_INFO(...) lightning::Log(lightning::LogType::Info, __VA_ARGS__)
#define LIGHTNING_LOG_WARNING(...) lightning::Log(lightning::LogType::Warning, __VA_ARGS__)
#define LIGHTNING_LOG_ERROR(...) lightning::Log(lightning::LogType::Error, __VA_ARGS__)
#define LIGHTNING_LOG_EVENT(...) lightning::Log(lightning::LogType::Event, __VA_ARGS__)

// Debug logger
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)
#define LIGHTNING_LOG_INFO_DEBUG(...) lightning::Log_Debug(lightning::LogType::Info, "", __VA_ARGS__)
#define LIGHTNING_LOG_WARNING_DEBUG(...) lightning::Log_Debug(lightning::LogType::Warning, AT, __VA_ARGS__)
#define LIGHTNING_LOG_ERROR_DEBUG(...) lightning::Log_Debug(lightning::LogType::Error, AT, __VA_ARGS__)
#define LIGHTNING_LOG_EVENT_DEBUG(...) lightning::Log_Debug(lightning::LogType::Event, AT, __VA_ARGS__)

#ifdef DEBUG
#ifdef _MSC_VER
#define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__)
#define DEBUG_BREAK() __builtin_trap()
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#else
#define DEBUG_BREAK()
#endif

#ifdef DEBUG
#define LIGHTNING_ASSERT(check, ...) {if(!(check)){LIGHTNING_LOG_ERROR_DEBUG(__VA_ARGS__);} assert(check);}
#else
#define LIGHTNING_ASSERT(check, ...) {assert(check);}
#endif


#endif //CORE_LOGER_H

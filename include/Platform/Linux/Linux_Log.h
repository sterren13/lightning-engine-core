//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_LINUX_LOG_H
#define CORE_LINUX_LOG_H
#ifdef __linux__
#define NC "\e[0m"
    #define RED "\e[0;31m" // Console text color red
    #define GRN "\e[0;32m" // Console text color green
    #define YEL "\e[0;33m" // Console text color yellow
    #define CYN "\e[0;36m" // Console text color cyan
#endif

#endif //CORE_LINUX_LOG_H

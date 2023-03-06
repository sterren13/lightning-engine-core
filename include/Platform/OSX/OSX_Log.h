//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_OSX_LOG_H
#define CORE_OSX_LOG_H
#ifdef __APPLE__
#define NC "\e[0m"
    #define RED "\e[0;31m" // Set Console Color to Red
    #define GRN "\e[0;32m" // Set Console Color to Green
    #define YEL "\e[0;33m" // Set Console Color to Yellow
    #define CYN "\e[0;36m" // Set Console Color to Cyan
#endif

#endif //CORE_OSX_LOG_H

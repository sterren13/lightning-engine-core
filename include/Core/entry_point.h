//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_ENTRY_POINT_H
#define CORE_ENTRY_POINT_H
#include "Core/Application/Application.h"

namespace lightning {
    Application* CreateApplication(int argc, char** argv);

    int _main(int argc, char** argv){
        lightning::Application* app = lightning::CreateApplication(argc, argv);
        app->Run();
        delete app;
        return 0;
    }

} // lightning

#ifdef __linux__
int main(int argc, char** argv){
    return lightning::_main(argc, argv);
}
#elifdef __APPLE__
int main(int argc, char** argv){
        return lightning::_main(argc, argv);
}
#elif _WIN32
#include <Windows.h>
int main(int argc, char** argv){
    return lightning::_main(argc, argv);
}
#endif

#endif //CORE_ENTRY_POINT_H

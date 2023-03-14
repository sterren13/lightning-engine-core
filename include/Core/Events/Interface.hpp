//
// Created by sterr on 14/03/2023.
//

#ifndef CORE_INTERFACE_HPP
#define CORE_INTERFACE_HPP
#include <memory>
#include "Core/Log/Loger.h"

namespace lightning {
    template <typename T>
    class Interface {
    public:
        static void Register(T* type);

        static void Unregister(T* type);

        static T* Get();

        class Registrar : public T {
        public:
            Registrar() ;

            ~Registrar();
        };

    private:

        inline static std::unique_ptr<T>& GetInstance() {
            static std::unique_ptr<T> instance;
            return instance;
        }

        static T* instance;
        static bool s_instance ;
    };
};

template <typename T>
void lightning::Interface<T>::Register(T* type) {
    if (!type){
        LIGHTNING_LOG_ERROR("Interface::Register: type is null");
        return;
    }
    if (GetInstance()){
        LIGHTNING_LOG_ERROR("Interface::Register: type is already registered");
        return;
    }
    GetInstance() = std::unique_ptr<T>(type);
}

template <typename T>
void lightning::Interface<T>::Unregister(T* type) {
    if(GetInstance().get() != type){
        LIGHTNING_LOG_ERROR("Interface::Unregister: type is not registered");
        return;
    }

    GetInstance().reset();
}

template <typename T>
T* lightning::Interface<T>::Get() {
    return GetInstance().get();
}

template <typename T>
lightning::Interface<T>::Registrar::Registrar() {
    Interface<T>::Register(this);
}

template <typename T>
lightning::Interface<T>::Registrar::~Registrar() {
    Interface<T>::Unregister(this);
}

#endif //CORE_INTERFACE_HPP

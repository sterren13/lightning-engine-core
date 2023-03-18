//
// Created by sterr on 16/03/2023.
//

#ifndef CORE_EBUSIMPLEMENTATION_HPP
#define CORE_EBUSIMPLEMENTATION_HPP
#include <vector>
#include "EBusTraits.hpp"
#include "Core/Log/Loger.h"

namespace lightning {
/*
 * Base EBus Implementation
 */
    template<class Interface, class Traits, EBusHandlerPolicy handlerPolicy = Traits::HandlerPolicy, EBusAddressPolicy addressPolicy = Traits::AddressPolicy>
    class EBusImplementation {
    public:
        template<typename M, typename... Args>
        static void Broadcast(void(M::*method)(Args...), Args &&... args) {
            LIGHTNING_LOG_ERROR("EBusImplementation::Broadcast() not implemented for this EBus");
        }

        template<typename R, typename M, typename... Args>
        static void BroadcastResult(R &ReturnVal, R(M::*method)(Args...), Args &&... args) {
            LIGHTNING_LOG_ERROR("EBusImplementation::BroadcastResult() not implemented for this EBus");
        }

        static void Connect(Interface *handler) {
            LIGHTNING_LOG_ERROR("EBusImplementation::Connect() not implemented for this EBus");
        }

        static void Disconnect(Interface *handler) {
            LIGHTNING_LOG_ERROR("EBusImplementation::Disconnect() not implemented for this EBus");
        }
    };

/*
 * EBus Implementation for EBusHandlerPolicy::Single and EBusAddressPolicy::Single
 */
    template<class Interface, class Traits>
    class EBusImplementation<Interface, Traits, EBusHandlerPolicy::Single, EBusAddressPolicy::Single> {
    public:
        template<typename M, typename... Args>
        static void Broadcast(void(M::*method)(Args...), Args &&... args) {
            LIGHTNING_ASSERT(GetHandler() != nullptr, "EBusImplementation::Broadcast() EBus has no handler");
            (GetHandler()->*method)(args...);
        }

        template<typename R, typename M, typename... Args>
        static void BroadcastResult(R &ReturnVal, R(M::*method)(Args...), Args &&... args) {
            LIGHTNING_ASSERT(GetHandler() != nullptr, "EBusImplementation::BroadcastResult() EBus has no handler");
            ReturnVal = (GetHandler()->*method)(args...);
        }

        static void Connect(Interface *handler) {
            if (GetHandler() != nullptr)
                LIGHTNING_LOG_ERROR("EBusImplementation::Connect() EBus already has a handler");
            GetHandler() = handler;
        }

        static void Disconnect(Interface *handler) {
            if (GetHandler() == handler)
                GetHandler() = nullptr;
        }

    private:
        static Interface*& GetHandler() {
            static Interface *m_Handler = nullptr;
            return m_Handler;
        }
    };

/*
 * EBus Implementation for EBusHandlerPolicy::Multiple and EBusAddressPolicy::Single
 */
    template<class Interface, class Traits>
    class EBusImplementation<Interface, Traits, EBusHandlerPolicy::Multiple, EBusAddressPolicy::Single> {
        template<typename M, typename... Args>
        static void Broadcast(void(M::*method)(Args...), Args &&... args) {
            for (auto handler:  GetHandlers()) {
                (handler->*method)(args...);
            }
        }

        template<typename R, typename M, typename... Args>
        // TODO EBus Implementation for EBusHandlerPolicy::Multiple and EBusAddressPolicy::Single chek if BroadcastResult can be deleted
        static void BroadcastResult(R &ReturnVal, R(M::*method)(Args...), Args &&... args) {
            LIGHTNING_LOG_ERROR("EBusImplementation::BroadcastResult() not implemented for this EBus");
        }

        static void Connect(Interface *handler) {
            GetHandlers().push_back(handler);
        }

        static void Disconnect(Interface *handler) {
            for (auto it =  GetHandlers().begin(); it !=  GetHandlers().end(); it++) {
                if (*it == handler) {
                    GetHandlers().erase(it);
                    break;
                }
            }
        }

    private:
        static std::vector<Interface *>& GetHandlers() {
            static std::vector<Interface *> m_Handlers;
            return m_Handlers;
        }
    };

/*
 * EBus Implementation for EBusHandlerPolicy::Single and EBusAddressPolicy::ById
 */
    template<class Interface, class Traits>
    class EBusImplementation<Interface, Traits, EBusHandlerPolicy::Single, EBusAddressPolicy::ById> {
        template<typename M, typename... Args>
        static void Broadcast(void(M::*method)(Args...), Args &&... args) {

        }

        template<typename R, typename M, typename... Args>
        static void BroadcastResult(R &ReturnVal, R(M::*method)(Args...), Args &&... args) {

        }
    };

/*
 * EBus Implementation for EBusHandlerPolicy::Multiple and EBusAddressPolicy::ById
 */
    template<class Interface, class Traits>
    class EBusImplementation<Interface, Traits, EBusHandlerPolicy::Multiple, EBusAddressPolicy::ById> {
        template<typename M, typename... Args>
        static void Broadcast(void(M::*method)(Args...), Args &&... args) {

        }

        template<typename R, typename M, typename... Args>
        static void BroadcastResult(R &ReturnVal, R(M::*method)(Args...), Args &&... args) {

        }
    };

/*
 * EBus Implementation for EBusHandlerPolicy::Multiple and EBusAddressPolicy::ById
 */
    template<class Interface, class Traits>
    class EBusImplementation<Interface, Traits, EBusHandlerPolicy::Single, EBusAddressPolicy::ByIdAndOrder> {
        template<typename M, typename... Args>
        static void Broadcast(void(M::*method)(Args...), Args &&... args) {

        }

        template<typename R, typename M, typename... Args>
        static void BroadcastResult(R &ReturnVal, R(M::*method)(Args...), Args &&... args) {

        }
    };

/*
 * EBus Implementation for EBusHandlerPolicy::Single and EBusAddressPolicy::ByIdAndOrder
 */
    template<class Interface, class Traits>
    class EBusImplementation<Interface, Traits, EBusHandlerPolicy::Multiple, EBusAddressPolicy::ByIdAndOrder> {
        template<typename M, typename... Args>
        static void Broadcast(void(M::*method)(Args...), Args &&... args) {

        }

        template<typename R, typename M, typename... Args>
        static void BroadcastResult(R &ReturnVal, R(M::*method)(Args...), Args &&... args) {

        }
    };
}
#endif //CORE_EBUSIMPLEMENTATION_HPP

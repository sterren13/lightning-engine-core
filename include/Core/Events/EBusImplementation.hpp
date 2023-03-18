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
 * Max one handler per EBus
 * Max one address per EBus
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
 * Multiple handlers per EBus
 * Max one address per EBus
 */
    template<class Interface, class Traits>
    class EBusImplementation<Interface, Traits, EBusHandlerPolicy::Multiple, EBusAddressPolicy::Single> {
    public:
        template<typename M, typename... Args>
        static void Broadcast(void(M::*method)(Args...), Args &&... args) {
            for (auto handler:  GetHandlers()) {
                (handler->*method)(args...);
            }
        }

        template<typename Lambda, typename R, typename M, typename... Args>
        static void BroadcastResult(R(M::*method)(Args...), Lambda lambda, Args &&... args) {
            for (auto handler:  GetHandlers()) {
                R val = (handler->*method)(args...);
                lambda(val);
            }
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
 * Multiple handlers per EBus which are identified by an ID
 * Max one handler per address
 * TODO: Implement Ebus implementation for EBusHandlerPolicy::Single and EBusAddressPolicy::ById
 */
    template<class Interface, class Traits>
    class EBusImplementation<Interface, Traits, EBusHandlerPolicy::Single, EBusAddressPolicy::ById> {
    public:
        template<typename M, typename... Args>
        static void Broadcast(void(M::*method)(Args...), Args &&... args) {

        }

        template<typename R, typename M, typename... Args>
        static void BroadcastResult(R &ReturnVal, R(M::*method)(Args...), Args &&... args) {

        }
        static void Connect(Interface *handler) {

        }
        static void Disconnect(Interface *handler) {

        }
    };

/*
 * EBus Implementation for EBusHandlerPolicy::Multiple and EBusAddressPolicy::ById
 * Multiple handlers per EBus which are identified by an ID
 * Multiple handlers per address
 * TODO Implement EBus Implementation for EBusHandlerPolicy::Multiple and EBusAddressPolicy::ById
 */
    template<class Interface, class Traits>
    class EBusImplementation<Interface, Traits, EBusHandlerPolicy::Multiple, EBusAddressPolicy::ById> {
    public:
        template<typename M, typename... Args>
        static void Broadcast(void(M::*method)(Args...), Args &&... args) {

        }

        template<typename R, typename M, typename... Args>
        static void BroadcastResult(R &ReturnVal, R(M::*method)(Args...), Args &&... args) {

        }
        static void Connect(Interface *handler) {

        }
        static void Disconnect(Interface *handler) {

        }
    };

/*
 * EBus Implementation for EBusHandlerPolicy::Multiple and EBusAddressPolicy::ById
 * Multiple handlers per EBus which are identified by an ID
 * Max one handler per address
 * Ordered by ID
 * TODO Implement EBus Implementation for EBusHandlerPolicy::Single and EBusAddressPolicy::byIdAndOrder
 */
    template<class Interface, class Traits>
    class EBusImplementation<Interface, Traits, EBusHandlerPolicy::Single, EBusAddressPolicy::ByIdAndOrder> {
    public:
        template<typename M, typename... Args>
        static void Broadcast(void(M::*method)(Args...), Args &&... args) {

        }

        template<typename R, typename M, typename... Args>
        static void BroadcastResult(R &ReturnVal, R(M::*method)(Args...), Args &&... args) {

        }
        static void Connect(Interface *handler) {

        }
        static void Disconnect(Interface *handler) {

        }
    };

/*
 * EBus Implementation for EBusHandlerPolicy::Single and EBusAddressPolicy::ByIdAndOrder
 * Multiple handlers per EBus which are identified by an ID
 * Multiple handlers per address
 * Ordered by ID
 * TODO Implement EBus Implementation for EBusHandlerPolicy::Multiple and EBusAddressPolicy::byIdAndOrder
 */
    template<class Interface, class Traits>
    class EBusImplementation<Interface, Traits, EBusHandlerPolicy::Multiple, EBusAddressPolicy::ByIdAndOrder> {
    public:
        template<typename M, typename... Args>
        static void Broadcast(void(M::*method)(Args...), Args &&... args) {

        }

        template<typename R, typename M, typename... Args>
        static void BroadcastResult(R &ReturnVal, R(M::*method)(Args...), Args &&... args) {

        }
        static void Connect(Interface *handler) {

        }
        static void Disconnect(Interface *handler) {

        }
    };
}
#endif //CORE_EBUSIMPLEMENTATION_HPP

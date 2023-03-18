//
// Created by sterr on 15/03/2023.
//

#ifndef CORE_EBUS_HPP
#define CORE_EBUS_HPP
#include "EBusTraits.hpp"
#include "EBusImplementation.hpp"

/*
 * The EBus is a base class for all EBus implementations.
 * TODO: add que to EBus whit template parameter
 * TODO: add mutex to EBus whit template parameter
 * TODO: add Event to call when a handler is connected or disconnected whit template parameter
 */
namespace lightning {
    template<class Interface, class BusTraits = Interface>
    class EBus :
            public EBusImplementation<Interface, BusTraits> {};
}
#endif //CORE_EBUS_HPP

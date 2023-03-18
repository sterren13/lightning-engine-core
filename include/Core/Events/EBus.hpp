//
// Created by sterr on 15/03/2023.
//

#ifndef CORE_EBUS_HPP
#define CORE_EBUS_HPP
#include "EBusTraits.hpp"
#include "EBusImplementation.hpp"

namespace lightning {
    template<class Interface, class BusTraits = Interface>
    class EBus :
            public EBusImplementation<Interface, BusTraits> {};
}
#endif //CORE_EBUS_HPP

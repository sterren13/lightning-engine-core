//
// Created by sterr on 15/03/2023.
//

#ifndef CORE_EBUS_HPP
#define CORE_EBUS_HPP
#include "EBusTraits.hpp"

template <class Interface, class BusTraits = Interface>
class EBus {
public:
    static void Connect();
    static void Disconnect();

private:

};
#endif //CORE_EBUS_HPP

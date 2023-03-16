//
// Created by sterr on 16/03/2023.
//

#ifndef CORE_EBUSIMPLEMENTATION_HPP
#define CORE_EBUSIMPLEMENTATION_HPP

template <class Bus, class Traits>
class EBusBroadcaster {

};

template <class Bus, class Traits>
class EBusImplementation :
        public EBusBroadcaster<Bus, Traits>
{
};

#endif //CORE_EBUSIMPLEMENTATION_HPP

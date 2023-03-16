//
// Created by sterr on 15/03/2023.
//

#ifndef CORE_EBUSTRAITS_HPP
#define CORE_EBUSTRAITS_HPP

// EBus Policies
enum class EBusHandlerPolicy {
    /**
     * The EBus Has one handler for each address.
     */
    Single,

    /**
     * The EBus Has multiple handlers for each address.
     * Handlers receive events in the order they were connected.
     */
    Multiple
};

enum class EBusAddressPolicy {
    /**
     * The EBus Has one address.
     */
    Single,

    /**
     * The EBus Has multiple addresses.
     * Events are dispatched to all handlers when no id was specified.
     * When an id is specified, events are dispatched to all handlers with that id.
     */
    ById,

    /**
     * The EBus Has multiple addresses.
     * Events are dispatched to all handlers when no id was specified.
     * The order of handlers is specified in the order policy fo the EBusTrait.
     * When an id is specified, events are dispatched to the handler with that id.
     */
    ByIdAndOrder
};

class EBusTraits {
public:
    /**
     * The EBus Handler Policy.
     */
    static constexpr EBusHandlerPolicy HandlerPolicy = EBusHandlerPolicy::Single;

    /**
     * The EBus Address Policy.
     */
    static constexpr EBusAddressPolicy AddressPolicy = EBusAddressPolicy::Single;

    /**
     * The EBus Id Type.
     */
    using BusIdType = int;
};

#endif //CORE_EBUSTRAITS_HPP

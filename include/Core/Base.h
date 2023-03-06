//
// Created by sterr on 5/03/2023.
//

#ifndef CORE_BASE_H
#define CORE_BASE_H
#include <memory>

namespace lightning {
    // scope
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args && ... args) {
        return std::make_unique<T>(std::forward<Args>(args) ...);
    }

    // ref
    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args && ... args) {
        return std::make_shared<T>(std::forward<Args>(args) ...);
    }

}// lightning

#endif //CORE_BASE_H

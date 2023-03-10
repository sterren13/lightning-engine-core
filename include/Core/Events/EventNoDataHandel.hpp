//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_EVENTNODATAHANDEL_HPP
#define CORE_EVENTNODATAHANDEL_HPP
#include <queue>
#include <vector>
#include <functional>

namespace lightning {
    /*
     * EventNoDataHandel can be used to run callbacks when an event is called
     */
    class EventNoDataHandel {
    public:

        // call Event
        void CallEvent(){
            EventIsCalled = true;
        }

        // run all registered callbacks
        void RunCallback() {
            if(EventIsCalled){
                for (auto& callback : m_callbacks) {
                    callback();
                }
                EventIsCalled = false;
            }
        }

        // Register a callback to be called when RunCallback is called
        size_t RegisterListener(std::function<void()> callback) {
            m_callbacks.push_back(callback);
            return m_callbacks.size() - 1;
        }

        // Unregister a callback by id
        void UnregisterListener(size_t id) {
            m_callbacks.erase(m_callbacks.begin() + id);
        }

    private:
        std::vector<std::function<void()>> m_callbacks; // list of callbacks
        bool EventIsCalled = false; // is event called
    };
}
#endif //CORE_EVENTNODATAHANDEL_HPP

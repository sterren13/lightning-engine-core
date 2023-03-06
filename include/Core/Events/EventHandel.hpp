//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_EVENTHANDEL_HPP
#define CORE_EVENTHANDEL_HPP
#include <queue>
#include <vector>
#include <functional>

#include "Core/Log/Loger.h"

namespace lightning {
    class BaseEventHandel {
    public:
        virtual ~BaseEventHandel() = default;
        virtual void RunCallback() = 0;
        virtual size_t size() = 0;
    };

    /*
     * EventHandel is a class that can be used to queue events and run callbacks for each event in the queue
     * T is the type of the event
     */
    template<typename T>
    class EventHandel : public BaseEventHandel {
    public:
        // add an event to the queue
        void Push(T event) {
            m_events.push(event);
        }

        // run all registered callbacks for all events in the queue
        void RunCallback() override {
            while (!m_events.empty()) {
                for (auto& callback : m_callbacks) {
                    callback(m_events.front());
                }
                m_events.pop();
            }
        }

        // Register a callback to be called when RunCallback is called for each event in the queue
        size_t RegisterListener(std::function<void(T)> callback) {
            m_callbacks.push_back(std::move(callback));
            return m_callbacks.size() - 1;
        }

        // Unregister a callback
        void UnregisterListener(size_t id) {
            LIGHTNING_ASSERT(id < m_callbacks.size(), "Invalid callback id");
            m_callbacks.erase(m_callbacks.begin() + id);
        }

        // Get the number of events in the queue
        size_t size() override {
            return m_events.size();
        }

    private:
        std::vector<std::function<void(T)>> m_callbacks; // list of callbacks
        std::queue<T> m_events; // queue of all events
    };
}

#endif //CORE_EVENTHANDEL_HPP

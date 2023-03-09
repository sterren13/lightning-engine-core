//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_EVENTBUS_HPP
#define CORE_EVENTBUS_HPP
#include <unordered_map>
#include "EventHandel.hpp"
#include "Core/Base.h"
#include "Core/Log/Loger.h"
#include "EventNoDataHandel.hpp"

namespace lightning {
    // bind a function from a class instance
    #define ENGINE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) \
                                    { return this->fn(std::forward<decltype(args)>(args)...); }
    class EventBus {
    public:
        typedef size_t EventID;
    public:
        // Register an event type
        template<typename T>
        void RegisterEvent(){
            HandelMap.insert({typeid(T).hash_code(), m_eventHandles.size()});
            m_eventHandles.push_back(CreateRef<EventHandel<T>>());
        }

        // Register an event without data
        void RegisterEvent(const char* name){
            m_EventNoDataMap.insert({name, m_EventNoDataHandles.size()});
            m_EventNoDataHandles.push_back(CreateRef<EventNoDataHandel>());
        }

        // Remove an event type
        template<typename T>
        void RemoveEvent(){
            EventID id = typeid(T).hash_code();
            m_eventHandles.erase(m_eventHandles.begin() + HandelMap[id]);
            HandelMap.erase(id);
        }

        // Remove an event without data
        void RemoveEvent(const char* name){
            m_EventNoDataHandles.erase(m_EventNoDataHandles.begin() + m_EventNoDataMap[name]);
            m_EventNoDataMap.erase(name);
        }

        // Push an event
        template<typename T>
        void PushEvent(T event){
            GetEventHandel<T>()->Push(event);
        }

        // Push an event without data
        void PushEvent(const char* name){
            LIGHTNING_LOG_EVENT("Pushing event: ", name);
            m_EventNoDataHandles[m_EventNoDataMap[name]]->CallEvent();
        }

        // Register a callback to be called when an event is pushed
        template<typename T>
        size_t RegisterListener(std::function<void(T)> callback){
            return GetEventHandel<T>()->RegisterListener(callback);
        }

        // Register a callback to be called when an event without data is pushed
        size_t RegisterListener(const char* name, std::function<void()> callback){
            LIGHTNING_LOG_EVENT("Registering event: ", name);
            return m_EventNoDataHandles[m_EventNoDataMap[name]]->RegisterListener(callback);
        }

        // Unregister a callback by id
        template<typename T>
        void RemoveListener(size_t id){
            GetEventHandel<T>()->UnregisterListener(id);
        }

        // Unregister a callback by id
        void RemoveListener(const char* name, size_t id2){
            m_EventNoDataHandles[m_EventNoDataMap[name]]->UnregisterListener(id2);
        }

        // Run all callbacks for all events
        void ProcessEvents(){
            for(auto& handel : m_eventHandles){
                handel->RunCallback();
            }
            for(auto& handel : m_EventNoDataHandles){
                handel->RunCallback();
            }
        }

    private:
        template<typename T>
        Ref<EventHandel<T>> GetEventHandel(){
            LIGHTNING_ASSERT(HandelMap.find(typeid(T).hash_code()) != HandelMap.end(), "Event not registered");
            EventID id = typeid(T).hash_code();

            return std::static_pointer_cast<EventHandel<T>>(m_eventHandles[HandelMap[id]]);
        }
    private:
        std::vector<Ref<BaseEventHandel>> m_eventHandles; // list of event handles
        std::unordered_map<EventID , size_t> HandelMap; // map of event types to handel index
        std::vector<Ref<EventNoDataHandel>> m_EventNoDataHandles; // list of free handel indexes
        std::unordered_map<const char* , size_t> m_EventNoDataMap; // map of event types to handel index
    };
}
#endif //CORE_EVENTBUS_HPP

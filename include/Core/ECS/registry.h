//
// Created by sterr on 5/03/2023.
//

#ifndef LIGHTNING_ENGINE_CORE_REGISTRY_H
#define LIGHTNING_ENGINE_CORE_REGISTRY_H
#include <vector>
#include <unordered_set>
#include "Core/Types.h"
#include "View.hpp"

namespace lightning::ECS {
    /*
     * Registry is the main class for the ECS
     */
    class registry {
    public:
        // create new entity
        Entity_t CreateEntity();

        // destroy entity
        void DestroyEntity(Entity_t entity); // TODO add global list of component pools for destruction entity

        // check if is still active
        bool IsActive(Entity_t entity);

        // get number of entities
        size_t size() const { return Entitys.size(); }

        // get begin iterator
        auto begin() { return Entitys.begin();}

        // get end iterator
        auto end() { return Entitys.end();}

        // get component pool for type
        template<typename T>
        Component_Pool<T>& Get_Pool(){
            static Component_Pool<T> pool;
            return pool;
        }

        // check if entity has component
        template<typename T>
        bool Has(Entity_t entity){
            return Get_Pool<T>().Has(entity);
        }

        // make view of entities with components
        template<typename ... Ts>
        View<Ts...> ViewEntities(){
            std::vector<Entity_t> Entity_list;
            for (auto& entity : Entitys){
                if (Has_for_each<Ts...>()){
                    Entity_list.push_back(entity);
                }
            }
            return View<Ts...>(Entity_list, Get_Pool<Ts>()...);
        }

    private:
        template<typename T>
        bool Has_for_each(Entity_t entity) {
            if (Has<T>(entity))
                return true;
            return false;
        }

        template<typename T, typename... Ts>
        bool Has_for_each(Entity_t entity, std::enable_if_t<sizeof...(Ts) != 0>* = nullptr) {
            if (Has<T>(entity))
                return Has_for_each<Ts...>(entity);
            return false;
        }

    private:
        std::vector<Entity_t> Entitys; // list of active entities
        std::unordered_set<Entity_t> EntitysSet; // set of active entities
        std::vector<Entity_t> FreeEntitys; // list of free entities
        Entity_t NextEntity = 0; // next entity id
    };
} // ECS

#endif //LIGHTNING_ENGINE_CORE_REGISTRY_H

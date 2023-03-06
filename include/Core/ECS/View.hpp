//
// Created by sterr on 5/03/2023.
//

#ifndef CORE_VIEW_HPP
#define CORE_VIEW_HPP
#include <vector>
#include <tuple>
#include "Component_Pool.hpp"
#include "Core/Types.h"

namespace lightning {
    namespace ECS {
        /*
         * View is a view on a set of entities and their components
         * TODO add support for not coomponents of entities
         *  eg. view of all entities with position and velocity but not mass
         */

        template<typename ... Ts>
        class View{
        public:
            struct Component_Job_Base{
                virtual void Update(Entity_t, Ts& ...) = 0;
            };

        public:
            View(std::vector<Entity_t> Entity_list, Component_Pool<Ts>&... pools) : Entitys(std::move(Entity_list)), types(pools...){}

            // get component pool for type
            template<typename T>
            Component_Pool<T>& Get_Pool(){
                return std::get<Component_Pool<T>&>(types);
            }

            // get component data for entity
            template<typename T>
            T& Get(Entity_t entity){
                return Get_Pool<T>().GetFast(entity);
            }

            // set component data for entity
            template<typename T>
            void Set(Entity_t entity, T data){
                Get_Pool<T>().Set(entity, data);
            }

            // get number of entities in view
            inline size_t size() const {return Entitys.size();}

            // get begin iterator
            auto begin(){
                return Entitys.begin();
            }

            // get end iterator
            auto end(){
                return Entitys.end();
            }

            // run lambda on each entity
            template<typename Func>
            void ForEach(Func& func){
                auto it = Entitys.begin();
                while (it != Entitys.end()){
                    func(*it, Get<Ts>(*it)...);
                    it++;
                }
            }

            // run job on each entity
            void ForEach(Component_Job_Base& job){
                auto it = Entitys.begin();
                while (it != Entitys.end()){
                    job.Update(*it, Get<Ts>(*it)...);
                    it++;
                }
            }

        private:
            std::tuple<Component_Pool<Ts>&...> types;
            std::vector<Entity_t> Entitys;
        };
    } // ECS
} // lightning
#endif //CORE_VIEW_HPP

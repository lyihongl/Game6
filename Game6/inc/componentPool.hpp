#pragma once
#include <bitset>
#include <cstdlib>
#include <string>
#include <tuple>
#include <vector>
#include "Sprite.hpp"
#include "components/Position2D.hpp"
#include "components/collider2d.hpp"
#include "components/physics2d.hpp"
#include "quad.hpp"

// clang-format off
typedef std::tuple<
    std::vector<Position2D>,
    std::vector<Physics2D>, 
    std::vector<Collider2D>, 
    std::vector<Quad>, 
    std::vector<Sprite>
> EntityComponentVectorTuple;
// clang-format on

//void reset_all_at(EntityComponentVectorTuple& pool,
//                  std::integer_sequence<T, ints...> int_seq, const size_t id) {
//    std::get<ints>(pool)[id].reset();
//}

template <size_t I, typename T, typename Tuple_t>
constexpr size_t index_in_tuple_fn() {
    static_assert(I < std::tuple_size<Tuple_t>::value,
                  "The element is not in the tuple");

    typedef typename std::tuple_element<I, Tuple_t>::type el;
    if constexpr (std::is_same<T, el>::value) {
        return I;
    } else {
        return index_in_tuple_fn<I + 1, T, Tuple_t>();
    }
}

template <typename T, typename Tuple_t>
struct index_in_tuple {
    static constexpr size_t value = index_in_tuple_fn<0, T, Tuple_t>();
};

template <typename T>
using componentIndex =
    index_in_tuple<std::vector<T>, EntityComponentVectorTuple>;

class ComponentPool {
    std::size_t numEntities;
    std::vector<bool> active;
    std::vector<std::string> tags;
    std::vector<std::bitset<std::tuple_size_v<EntityComponentVectorTuple>>>
        componentActive;
    EntityComponentVectorTuple pool;
    ComponentPool(size_t maxEntities);
    std::size_t getNextIndex() const;

   public:
    static ComponentPool& Instance();
    const std::string& getTag(size_t id) const;
    void deactivateEntity(size_t id);
    std::size_t addEntity(const std::string& tag);

    template <typename T>
    bool getComponentActive(size_t id) {
        return componentActive[id][componentIndex<T>::value];
    }

    template <typename T>
    T& getComponent(size_t id) {
        if (!getComponentActive<T>(id))
            throw -1;
        return std::get<std::vector<T>>(pool)[id];
    }

    template <typename T>
    void activateComponent(size_t id) {
        componentActive[id][componentIndex<T>::value] = true;
    }

    template <typename T>
    void setComponent(size_t id, const T& c) {
        componentActive[id][componentIndex<T>::value] = true;
        std::get<std::vector<T>>(pool)[id] = c;
    }

    template <typename T>
    void setComponent(size_t id, const T&& c) {
        componentActive[id][componentIndex<T>::value] = true;
        std::get<std::vector<T>>(pool)[id] = c;
    }
};
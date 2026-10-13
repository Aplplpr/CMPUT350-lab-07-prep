#ifndef PACK_H
#define PACK_H

#include <type_traits>

namespace pack_detail {

template <typename... Args> //count # of types in the pack
constexpr int packSize = sizeof...(Args);

template <int QueryIndex, typename... Args> //handle invalid indices (empty pack or out of range)
struct _packIndexToType {static_assert(QueryIndex >= 0 && QueryIndex < sizeof...(Args), "Index out of range.");
};

template <int QueryIndex, typename First, typename... Rest> //recursive specialization skip the first type until index is 0
struct _packIndexToType<QueryIndex, First, Rest...> {static_assert(QueryIndex > 0 && QueryIndex < 1 + sizeof...(Rest), "Index out of range.");
    using type = typename _packIndexToType<QueryIndex - 1, Rest...>::type;
};

template <typename First, typename... Rest> //base case
struct _packIndexToType<0, First, Rest...> {
    using type = First;
};

template <int QueryIndex, typename... Args> //alias
using packIndexToType = typename _packIndexToType<QueryIndex, Args...>::type;

template <int Accumulated, typename QueryType, typename... Args> //return -1 if the type is not found
constexpr int _packTypeToIndex = -1;

template <int Accumulated, typename QueryType, typename First, typename... Rest> //recursive: compare types and move to the next index if different
constexpr int _packTypeToIndex<Accumulated, QueryType, First, Rest...> =
    std::is_same_v<QueryType, First> ? Accumulated :
    _packTypeToIndex<Accumulated + 1, QueryType, Rest...>;

template <typename QueryType, typename... Args> //searching for the type from index 0
constexpr int packTypeToIndex = _packTypeToIndex<0, QueryType, Args...>;

}

template <typename... Args>
struct Pack {
    static constexpr int size = pack_detail::packSize<Args...>; //# of types in pack

    template <int QueryIndex> //type at given index
    using type = pack_detail::packIndexToType<QueryIndex, Args...>;

    template <typename QueryType> //first index of given type
    static constexpr int index = pack_detail::packTypeToIndex<QueryType, Args...>;
};

#endif  // PACK_H

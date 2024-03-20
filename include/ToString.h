#pragma once

#include <bits/iterator_concepts.h>
#include <bits/utility.h>
#include <format>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#include <iterator>

namespace vtc {

template<typename T>
std::string ToString(const T& value) {
    return std::string(std::format("<{}>", typeid(T).name()));
}

template <typename T>
concept IOConvertible = requires(T value, std::stringstream strs)
{
    strs << value;
};

template <typename T>
concept ConvertibleToString = requires(T value)
{
    ToString(value);
};

template<typename T>
requires IOConvertible<T>
std::string ToString(const T& value)
{
    std::stringstream strs;
    strs << value;
    return strs.str();
}

template <typename T, typename U>
std::string ToString(const std::pair<T, U>& pair) 
{
    return std::format("({}, {})", vtc::ToString(pair.first), vtc::ToString(pair.second));
}

template<typename T>
requires requires(const T& value)
{
    { value.cbegin() };
    { value.cend() };
    { value.cbegin()++ };
    { value.cend()++ };
    { ToString(*value.cbegin()) };
    { ToString(*value.cend()) };
}
std::string ToString(const T& value)
{
    std::stringstream result;
    result << "[";
    auto iter = value.cbegin();
    while (iter != value.cend()) {
        result << ToString(*iter);
        auto iter_next = iter;
        iter_next++;
        if (iter_next != value.cend()) {
            result << ", ";
        }
        iter++;
    }
    result << "]";
    return  result.str();
}

template <unsigned long int I, typename... T>
concept InTupleBounds = requires(std::tuple<T...> tuple) {
    { (std::tuple_size_v<std::tuple<T...>>) > I };
};

template <unsigned long int Index, typename... T>
requires (InTupleBounds<Index, T...>)
std::string ToString(const std::tuple<T...>& asd)
{
    return ")";
}

template <unsigned long int Index = 0, typename... T>
std::string ToString(const std::tuple<T...>& value)
{
    if constexpr(!InTupleBounds<Index, T...>) {
        return ")";
    }
    
    std::stringstream result;
    if constexpr(Index == 0)
    {
        result << "(";
    }

    result << ToString(std::get<Index>(value));

    if constexpr(InTupleBounds<Index + 1, T...>)
    {
        result << ", ";
    }

    return result.str();
}



} // namespace vtc
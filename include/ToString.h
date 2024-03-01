#pragma once

#include <bits/iterator_concepts.h>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>

namespace vtc {

template<typename T>
std::string ToString(const T& value);

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

template<typename T>
requires requires(const T& value)
{
    { value.cbegin() } -> std::forward_iterator;
    { value.cend() } -> std::forward_iterator;
    { value.cbegin()++ };
    { value.cend()++ };
    { ToString(*value.cbegin()) } -> ConvertibleToString;
    { ToString(*value.cend()) } -> ConvertibleToString;
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

} // namespace vtc
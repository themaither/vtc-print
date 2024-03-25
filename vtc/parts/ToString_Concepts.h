#pragma once

#include <sstream>
namespace vtc {

template <typename T>
concept IOConvertible = requires(T value, std::stringstream strs)
{
    strs << value;
};

template <typename T>
concept ConvertibleToString = requires(T value)
{
    // ToString(value);
    true;
};

template <typename T>
concept ConstContainer = requires(T value)
{
    { value.cbegin() } -> std::forward_iterator;
    { value.cend() } -> std::forward_iterator;
};

template <typename T>
concept Container = requires(T value)
{
    { value.begin() } -> std::forward_iterator;
    { value.end() } -> std::forward_iterator;
};

}
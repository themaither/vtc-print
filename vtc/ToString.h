#pragma once

#include <format>
#include <string>
#include <utility>


#include "parts/ToString_Concepts.h"
    
namespace vtc {

template<typename T>
requires IOConvertible<T>
std::string ToString(const T& value)
{
    std::stringstream strs;
    strs << value;
    return strs.str();
}

// template<typename T>
// std::string ToString(const T& value) {
//     return std::string(std::format("<{}>", typeid(T).name()));
// }

template <typename T, typename U>
std::string ToString(const std::pair<T, U>& pair) 
{
    return std::format("({}, {})", vtc::ToString(pair.first), vtc::ToString(pair.second));
}

} // namespace vtc

#include "parts/ToString_Containers.h"
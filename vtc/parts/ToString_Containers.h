#pragma once
#include "vtc/parts/ToString_Concepts.h"
#include <sstream>

namespace vtc {

template<typename T>
requires Container<T>
std::string ToString(const T& value)
{
    std::stringstream result;
    result << "[";
    auto iter = value.cbegin();
    while (iter != value.cend()) {
        result << ToString(*iter);
        auto iter_next = iter;
        ++iter_next;
        if (iter_next != value.cend()) {
            result << ", ";
        }
        ++iter;
    }
    result << "]";
    return  result.str();
}

}
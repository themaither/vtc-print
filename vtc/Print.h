#pragma once
#include <iostream>
#include "ToString.h"

namespace vtc {

    template<typename T>
    concept ConvertibleToString = requires(T value) {
        vtc::ToString(value);
    };

    template <bool Newline = true>
    void Print() 
    {
        if constexpr (Newline) {
            std::cerr << "\n";
        }
    }
    
    template <bool Newline = true, ConvertibleToString T>
    void Print(const T& value) 
    {
        std::cerr << ToString(value);
        if constexpr (Newline) {
            std::cerr << "\n";
        }
    }
    
    template <bool Newline = true, ConvertibleToString T, ConvertibleToString ...TPack>
    void Print(const T& value, const TPack&... pack) 
    {
        Print<false, T>(value);
        Print<false, TPack...>(pack...);
        if constexpr (Newline) {
            std::cerr << "\n";
        }
    }

}
#pragma once
#include <iostream>
#include "ToString.h"

namespace vtc {
    template <bool Newline = true>
    void Print() 
    {
        if constexpr (Newline) {
            std::cerr << "\n";
        }
    }
    
    template <bool Newline = true, ConvertibleToString T>
    void Print(T value) 
    {
        std::cerr << ToString(value);
        if constexpr (Newline) {
            std::cerr << "\n";
        }
    }
    
    template <bool Newline = true, ConvertibleToString T, ConvertibleToString ...TPack>
    void Print(T value, TPack... pack) 
    {
        Print<false, T>(value);
        Print<false, TPack...>(pack...);
        if constexpr (Newline) {
            std::cerr << "\n";
        }
    }


}
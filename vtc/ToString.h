#include <concepts>
#include <cstdint>
#include <string>
#include <type_traits>

template <typename T>
struct Test {
    typedef T* pointer; 
};

namespace vtc {

    namespace _util {

        template <typename T>
        concept _StdConvertibleToString = requires(T value)
        {
            { std::to_string(value) } -> std::same_as<std::string>;
        };

    };

    template <typename T>
    std::string ToString(const T& value) 
    {
        if constexpr (std::constructible_from<std::string, T>) return value;
        if constexpr (_util::_StdConvertibleToString<T>) return std::to_string(value);
    }

}
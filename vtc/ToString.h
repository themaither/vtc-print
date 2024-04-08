#include <string>
#include <sstream>
#include <type_traits>
#include <vector>

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

    template <typename Iter>
    requires false
        || std::input_iterator<Iter>
        || std::is_pointer_v<Iter>
    std::string ToString(const Iter& left, const Iter& right)
    {
        std::stringstream result;
        result << "[";

        std::vector<Iter> items;

        for (Iter i = left; i != right; i++) {
            items.push_back(i);
        }

        for (size_t i = 0; i < items.size(); i++) {
            result << *items[i];
            if (i != items.size() - 1) {
                result << ", ";
            }
        }

        result << "]";

        return result.str();
    }

    template <typename T>
    std::string ToString(const T& value) 
    {
        if constexpr (std::constructible_from<std::string, T>) 
            return value;
        if constexpr (_util::_StdConvertibleToString<T>) 
            return std::to_string(value);
    }

}
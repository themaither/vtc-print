#include <string>
#include <sstream>
#include <type_traits>
#include <vector>

namespace vtc {

    namespace _util {

        template <typename T>
        concept _StdConvertibleToString = requires(T value)
        {
            { std::to_string(value) } -> std::same_as<std::string>;
        };

        template <typename T>
        concept _Iterable = requires(T value)
        {
            { value.begin() } -> std::input_iterator;
            { value.end() } -> std::input_iterator;
        };

        template <typename T>
        concept _CIterable = requires(T value)
        {
            { value.cbegin() } -> std::input_iterator;
            { value.cend() } -> std::input_iterator;
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
        // String-like types
        if constexpr (std::constructible_from<std::string, T>) 
            return value;

        // Numbers
        else if constexpr (_util::_StdConvertibleToString<T>) 
            return std::to_string(value);

        // Containers
        else if constexpr (_util::_CIterable<T>)
            return ToString(value.cbegin(), value.cend());
        else if constexpr (_util::_Iterable<T>)
            return ToString(value.begin(), value.end());

        // Fallback
        else
            #ifdef VTC_PRINT_USE_FALLBACK_TOSTRING
                return "<?>";
            #else
                static_assert(false, "Cannot convert value to string");
            #endif
    }

}
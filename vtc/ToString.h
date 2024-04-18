#pragma once
#include <string>
#include <sstream>
#include <tuple>
#include <type_traits>
#include <utility>
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

        template <typename T>
        concept _Tuplelike = requires(T value)
        {
            { std::get<0>(value) };
        };

        template <typename T>
        concept _Dereferencable = requires(T value)
        {
            { *value };
        };

        template <typename T>
        std::string _ToStringVariadicUtil(std::stringstream& ss, T value);

        template <typename T, typename ...U>
        std::string _ToStringVariadicUtil(std::stringstream& ss, T value, U... values);

        template <typename T, typename ...U>
        std::string _ToStringVariadic(T value, U... values);

        template <typename T>
        std::string _ToStringVariadic(T value);

        template <typename ...U>
        std::string _ToStringTuple(std::tuple<U...> tuple);

        template <typename ...U>
        std::string _ToStringTuple(std::pair<U...> pair);

        template <typename T>
        std::string _ToStringPointer(T value)
        {
            std::stringstream ss;
            if (value) {
                ss << "(" << value << ":" << *value << ")";
                return ss.str();
            }
            ss << "(" << value << ": " << "null" << ")";
            return ss.str();
        }

        template <typename T>
        std::string _ToStringNumber(T value)
        {
            if constexpr (std::integral<T>) {
                return std::to_string(value);
            }
            std::stringstream ss;
            ss << value;
            return ss.str();
        }

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
            return _util::_ToStringNumber(value);

        // Containers
        else if constexpr (_util::_CIterable<T>)
            return ToString(value.cbegin(), value.cend());
        else if constexpr (_util::_Iterable<T>)
            return ToString(value.begin(), value.end());

        // Tuple-like (i hate this)
        else if constexpr (_util::_Tuplelike<T>)
            return _util::_ToStringTuple(value);

        // Pointers
        else if constexpr (std::is_pointer_v<T>)
            return _util::_ToStringPointer(value);

        // Dereferencable types
        else if constexpr (_util::_Dereferencable<T>)
            return ToString(*value);

        // Fallback
        else
            #ifdef VTC_PRINT_USE_FALLBACK_TOSTRING
                return "<?>";
            #else
                static_assert(false, "Cannot convert value to string");
            #endif
    }

    namespace _util 
    {
        template <typename T>
        std::string _ToStringVariadicUtil(std::stringstream& ss, T value)
        {
            ss << ToString(value);
            return ss.str();
        }

        template <typename T, typename ...U>
        std::string _ToStringVariadicUtil(std::stringstream& ss, T value, U... values)
        {
            ss << ToString(value);
            ss << ", ";
            return _ToStringVariadicUtil(ss, values...);
        }

        template <typename T, typename ...U>
        std::string _ToStringVariadic(T value, U... values)
        {
            std::stringstream ss;
            ss << ToString(value);
            ss << ", ";
            return _ToStringVariadicUtil(ss, values...);
        }

        template <typename T>
        std::string _ToStringVariadic(T value)
        {
            std::stringstream ss;
            ss << ToString(value);
            return ss.str();
        }

        template <typename ...U>
        std::string _ToStringTuple(std::tuple<U...> tuple)
        {
            std::stringstream ss;

            ss << "(";
            ss << std::apply(_ToStringVariadic<U...>, tuple);
            ss << ")";
            return ss.str();
        }

        template <typename ...U>
        std::string _ToStringTuple(std::pair<U...> pair)
        {
            std::stringstream ss;

            ss << "(";
            ss << std::apply(_ToStringVariadic<U...>, pair);
            ss << ")";
            return ss.str();
        }
    }

}
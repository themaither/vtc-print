#include <stdexcept>
inline void TestFor(bool expression, const char* fail_message)
{
    if (!expression) {
        throw std::runtime_error(fail_message);
    }
}

#define TEST_FOR(expression) TestFor(expression, #expression)

#define TEST_FOR_NOTE(expression, note) TestFor(expression, note ": " #expression)
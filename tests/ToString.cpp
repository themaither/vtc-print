#include <ToString.h>
#include <deque>
#include <exception>
#include <iostream>
#include <list>
#include <set>
#include <sstream>
#include <unordered_set>
#include <vector>
#include "testing.h"

template<typename T>
inline void TestForContainerSorted()
{
    T v {1, 2, 3, 4};
    const char* name = typeid(T).name();
    TestFor(vtc::ToString(v) == "[1, 2, 3, 4]", name);
}

int main()
{
    {
        std::vector<int> v {1, 2, 3, 4};
        std::cout << vtc::ToString(v) << "\n";
    }
    
    
    TEST_FOR(vtc::ToString(5) == "5");

    TEST_FOR(vtc::ToString("Text") == "Text");

    TEST_FOR(vtc::ToString(2.3f) == "2.3");

    TEST_FOR(vtc::ToString(0.0f) == "0");

    TestForContainerSorted<std::vector<int>>();

    TestForContainerSorted<std::list<int>>();

    TestForContainerSorted<std::deque<int>>();

    TestForContainerSorted<std::set<int>>();
}
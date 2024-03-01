add_executable(ToString ToString.cpp)
add_test(NAME ToString COMMAND ToString)
target_include_directories(ToString PUBLIC ../include)
target_compile_options(ToString PUBLIC "-std=c++20")
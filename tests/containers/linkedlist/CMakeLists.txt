include_directories(${Akame_SOURCE_DIR}/include)
include_directories(${Akame_SOURCE_DIR}/depends/googletest/googletest/include)
link_directories(${Akame_SOURCE_DIR}/src/spike)
link_directories(${Akame_SOURCE_DIR}/depends/googletest/googlemock/gtest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Akame_SOURCE_DIR}/bin)

add_executable(linkedlist_test linkedlist_test.cpp)
target_link_libraries(linkedlist_test akame gtest gtest_main pthread)
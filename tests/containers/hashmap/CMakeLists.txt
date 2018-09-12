include_directories(${Akame_SOURCE_DIR}/include)
include_directories(${Akame_SOURCE_DIR}/depends/googletest/googletest/include)
link_directories(${Akame_SOURCE_DIR}/src/spike)
link_directories(${Akame_SOURCE_DIR}/depends/googletest/googlemock/gtest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Akame_SOURCE_DIR}/bin)

add_executable(hashmap_test hashmap_test.cpp)
target_link_libraries(hashmap_test akame gtest gtest_main pthread)
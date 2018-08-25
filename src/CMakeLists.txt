include_directories(${Akame_SOURCE_DIR}/include)
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(akame STATIC ${SRC_FILES})
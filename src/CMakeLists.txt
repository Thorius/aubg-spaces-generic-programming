
include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCE  main.cpp 
            revision.cpp)

set(HEADERS ${CMAKE_SOURCE_DIR}/include/buffer.hpp
            ${CMAKE_SOURCE_DIR}/include/revision.hpp)


add_executable(generic-programming ${SOURCE} ${HEADERS})
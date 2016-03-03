
include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCE  main.cpp 
            revision.cpp
            revision_2.cpp)

set(HEADERS ${CMAKE_SOURCE_DIR}/include/buffer.hpp
            ${CMAKE_SOURCE_DIR}/include/revision.hpp
            ${CMAKE_SOURCE_DIR}/include/revision_2.hpp
            ${CMAKE_SOURCE_DIR}/include/singleton.hpp)


add_executable(generic-programming ${SOURCE} ${HEADERS})
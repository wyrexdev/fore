cmake_minimum_required(VERSION 3.22.1)

project("fore")

file(GLOB_RECURSE SOURCES
        "*.cpp"
)

add_library(${CMAKE_PROJECT_NAME} SHARED
        ${SOURCES}
)

file(GLOB_RECURSE ALL_INCLUDE_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*/")

foreach(dir ${ALL_INCLUDE_DIRS})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${dir}")
        target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${dir}")
    endif()
endforeach()


target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log
        GLESv3
        EGL
)

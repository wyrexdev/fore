cmake_minimum_required(VERSION 3.22.1)

project("fore")

set(SOURCES
        main.cpp
        Core/Renderer.cpp
)

add_library(${CMAKE_PROJECT_NAME} SHARED
        ${SOURCES}
)

target_include_directories(${CMAKE_PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Core
        ${CMAKE_CURRENT_SOURCE_DIR}/Entities
)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log
        GLESv3
)

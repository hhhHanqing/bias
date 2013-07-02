cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(fly_sorter)

set(
    fly_sorter_FORMS 
    fly_sorter_window.ui 
    )

set(
    fly_sorter_HEADERS
    fly_sorter_window.hpp
    image_grabber.hpp
    parameters.hpp
    common.hpp
    )

set(
    fly_sorter_SOURCES
    fly_sorter_main.cpp
    fly_sorter_window.cpp
    image_grabber.cpp
    parameters.cpp
    )

qt4_wrap_ui(fly_sorter_FORMS_HEADERS ${fly_sorter_FORMS}) 
qt4_wrap_cpp(fly_sorter_HEADERS_MOC ${fly_sorter_HEADERS})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

add_executable(
    fly_sorter
    ${fly_sorter_FORMS_HEADERS}
    ${fly_sorter_HEADERS_MOC}
    ${fly_sorter_SOURCES} 
    )

add_dependencies(fly_sorter ${fly_sorter_FORMS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(.)
target_link_libraries(
    fly_sorter 
    ${QT_LIBRARIES} 
    ${bias_ext_link_LIBS} 
    bias_camera_facade
    bias_utility
    )



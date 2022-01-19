add_executable(test)

target_sources(test
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
)

target_include_directories(test
PUBLIC
    ${CMAKE_SOURCE_DIR}/xx_lib
    ${CMAKE_SOURCE_DIR}/vld/include
)

target_link_directories(test
PUBLIC
    ${CMAKE_SOURCE_DIR}/vld/lib/Win64
)

target_link_libraries(test
PUBLIC
    xx
    #vld
)
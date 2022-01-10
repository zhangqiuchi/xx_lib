add_library(xx STATIC)

target_sources(xx
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/point_struct.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/point_struct.h
)

target_include_directories(xx
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_SOURCE_DIR}/rapidjson/include
    ${CMAKE_SOURCE_DIR}/build/libbson/src/bson
    ${CMAKE_SOURCE_DIR}/libbson/src/bson
)

target_link_libraries(xx
PUBLIC
    bson_static
    msgpackc
)

target_compile_definitions(xx
PRIVATE
    BSON_STATIC
)

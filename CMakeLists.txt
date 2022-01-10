cmake_minimum_required(VERSION 3.20.0)

project(json_bson_msgpack)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmakeconf")

include(compiler_conf)
include(building_output)


add_subdirectory(rapidjson)
add_subdirectory(libbson)
add_subdirectory(msgpack-c)
add_subdirectory(xx_lib)

add_subdirectory(z_demo)
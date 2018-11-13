cmake_minimum_required(VERSION 2.8.12)

project(event2)





set(PATH_BD_INCLUDE ../../../libs/include CACHE PATH "path to the BD base module include folder")


# 相对路径转为绝对路径
function(transform_path path)
  if (NOT (${${path}} MATCHES "^/"))
    message(STATUS "transform relative path ${path} ${${path}}")
    unset(FIND_RES CACHE)
    find_path(FIND_RES ${${path}} PATHS ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR})
    set(${path} ${FIND_RES}/${${path}} PARENT_SCOPE)
  endif()
endfunction()

transform_path(PATH_BD_INCLUDE)

message(STATUS "PATH_BD_INCLUDE: ${PATH_BD_INCLUDE}")

include_directories(
  ${PATH_BD_INCLUDE})

 
add_executable(main main.cpp)
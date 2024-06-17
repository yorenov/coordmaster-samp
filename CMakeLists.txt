cmake_minimum_required (VERSION 3.26)

project ("CoordMaster"
  VERSION 1.0
)

set(USE_SAMPAPI ON)
set(USE_MINHOOK ON)
set(USE_RAKHOOK ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE PROJECT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE PROJECT_SOURCE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} SHARED
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCE_HEADERS}
    ${PROJECT_SOURCES}
)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/")

include(FetchContent)

if (USE_SAMPAPI)
  FetchContent_Declare(sampapi GIT_REPOSITORY https://github.com/BlastHackNet/SAMP-API.git GIT_TAG 6d4db99ab41f19d1a6a7c6cd48f5878bd1e14b62)
  FetchContent_MakeAvailable(sampapi)
  target_link_libraries(${PROJECT_NAME} PUBLIC sampapi)
endif ()

if (USE_MINHOOK)
  FetchContent_Declare(minhook GIT_REPOSITORY https://github.com/TsudaKageyu/minhook GIT_TAG 1cc46107ee522d7a5c73656c519ca16addf2c23a)
  FetchContent_MakeAvailable(minhook)
  target_link_libraries(${PROJECT_NAME} PUBLIC minhook)
endif ()

if (USE_RAKHOOK)
  FetchContent_Declare(RakHook GIT_REPOSITORY https://github.com/imring/RakHook.git GIT_TAG 625fd17897395997feb56ae293c7c07dbe49d26b)
  FetchContent_MakeAvailable(rakhook)
  target_link_libraries(${PROJECT_NAME} PUBLIC rakhook)
endif ()

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
    SUFFIX ".asi"
    RUNTIME_OUTPUT_DIRECTORY "C:/Games/GTASA/Clear"
)

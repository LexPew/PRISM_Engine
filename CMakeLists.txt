cmake_minimum_required(VERSION 3.28)
project(OpenGL LANGUAGES CXX C)
add_executable(${PROJECT_NAME})

file(GLOB sources 
${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
target_sources(${PROJECT_NAME} PRIVATE ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_LOCAL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

#FMT Library, GLM Library
include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 12.0.0) 
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0af55cc)
FetchContent_MakeAvailable(fmt glm)
#GLFW
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include/glfw)

#OpenGL
find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt glm::glm glfw OpenGL::GL )


    

add_executable(ogllearn main.cpp)
target_compile_features(ogllearn PRIVATE cxx_std_20)

add_subdirectory(world)
add_subdirectory(resource)
add_subdirectory(input)
add_subdirectory(types)

# internal dependencies
target_link_libraries(ogllearn
    PRIVATE
        resource
        world
        input
        types
)

# external depenencies
target_link_libraries(ogllearn
    PRIVATE
        stb::stb
        glm::glm
        glbinding::glbinding
        glbinding::glbinding-aux
        glfwpp::glfwpp
)

add_executable(ogllearn main.cpp)
target_compile_features(ogllearn PRIVATE cxx_std_20)

add_subdirectory(world)
add_subdirectory(gl-resource)
add_subdirectory(data-resource)
add_subdirectory(coupled-resource)
add_subdirectory(input)
add_subdirectory(types)

# internal dependencies
target_link_libraries(ogllearn
    PRIVATE
        glresource
        data-resource
        coupled-resource
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

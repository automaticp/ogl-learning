
set(
    EXTERNAL_DIRS
        glbinding
        glfwpp
        glm
        stb
        assimp
)

foreach(EXTERNAL_DIR ${EXTERNAL_DIRS})
    add_subdirectory(${EXTERNAL_DIR})
endforeach()


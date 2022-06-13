add_library(glresource INTERFACE)
target_sources(glresource INTERFACE GLResourceAllocators.h IGLResource.h GLShader.h GLShaderProgram.h GLTexture.h VAO.h VBO.h)
target_include_directories(glresource INTERFACE .)

# internal dependencies
target_link_libraries(glresource
    INTERFACE
        types
)

# external dependencies
target_link_libraries(glresource
    INTERFACE
        glm::glm
        glbinding::glbinding
        stb::stb
)

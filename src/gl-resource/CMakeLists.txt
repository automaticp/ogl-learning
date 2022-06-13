add_library(glresource INTERFACE)
target_sources(glresource INTERFACE GLResourceAllocators.h IGLResource.h GLShader.h GLShaderProgram.h GLTexture.h VAO.h VBO.h GLHandlePool.h)
target_include_directories(glresource INTERFACE .)

# internal dependencies
target_link_libraries(glresource
    INTERFACE
        types
        data-resource
)

# external dependencies
target_link_libraries(glresource
    INTERFACE
        glm::glm
        glbinding::glbinding
        stb::stb
)

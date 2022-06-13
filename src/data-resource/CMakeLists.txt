
add_library(data-resource INTERFACE IDataResource.h ResourceManager.h TextureData.h)

target_include_directories(data-resource INTERFACE .)
target_compile_features(data-resource INTERFACE cxx_std_20)

# external dependencies
target_link_libraries(data-resource
    INTERFACE
        assimp::assimp
        stb::stb
)

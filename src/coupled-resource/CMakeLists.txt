
add_library(coupled-resource INTERFACE ResourceCouple.h)

target_include_directories(coupled-resource INTERFACE .)
target_compile_features(coupled-resource INTERFACE cxx_std_20)

# internal dependencies
target_link_libraries(coupled-resource
    INTERFACE
        data-resource
        glresource
)


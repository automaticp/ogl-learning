#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <concepts>
#include "TextureData.h"
#include "GLTexture.h"
#include "IGLResource.h"

class GLHandlePool {
private:
    std::unordered_map<std::string, std::shared_ptr<IGLResource>> pool_;

public:
    template<std::derived_from<IGLResource> T>
    std::shared_ptr<T> get_handle(const std::string& path);

private:
    template<typename T, typename D>
    std::shared_ptr<T> find_or_load(const std::string& path) {
        auto it = pool_.find(path);
        if ( it != pool_.end() ) {
            return std::dynamic_pointer_cast<T>(*it);
        }
        else {
            auto data_ptr = DataPool::load<D>(path); // FIXME?
            auto emplaced_it{ emplace_from_data<T, D>(path, data_ptr) };
            return emplace_from_data<T, D>(path, data_ptr);
        }
    }

    template<typename T, typename D, typename ... OtherArgs>
    std::shared_ptr<T> emplace_from_data(const std::string& path, std::shared_ptr<D> data_ptr, OtherArgs&&... args) {
        auto [emplaced_it, was_emplaced]{ pool_.emplace(path, std::make_shared<T>(data_ptr, std::forward<OtherArgs>(args)...)) };
        return std::dynamic_pointer_cast<T>(*emplaced_it);
    }

};


template<>
inline std::shared_ptr<GLTexture> GLHandlePool::get_handle<GLTexture>(const std::string& path) {
    return find_or_load<GLTexture, TextureData>(path);
}




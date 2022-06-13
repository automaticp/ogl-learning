#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <concepts>
#include "IDataResource.h"

// A container and lifetime owner of data-like resources

class ResourceManager {
private:
    std::unordered_map<std::string, std::shared_ptr<IDataResource>> data_;

public:
    template<std::derived_from<IDataResource> T>
    std::shared_ptr<T> load(const std::string& path) {
        auto [emplaced_it, was_emplaced]{ data_.try_emplace(path, std::make_shared<T>(path)) };

        return std::dynamic_pointer_cast<T>(*emplaced_it);
    }
};

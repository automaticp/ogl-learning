#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <concepts>
#include "IDataResource.h"

// A container and lifetime owner of data-like resources

// Can be used both as a singleton (shared global resources),
// and as an instance (context specific resources)

class DataPool {
private:
    std::unordered_map<std::string, std::shared_ptr<IDataResource>> data_;

public:
    static std::shared_ptr<DataPool> singleton() {
        static std::shared_ptr<DataPool> global_pool;
        return global_pool;
    }

    template<std::derived_from<IDataResource> T>
    static std::shared_ptr<T> load(const std::string& path) {
        auto dp_ptr{ DataPool::singleton() };

        auto [emplaced_it, was_emplaced]{ dp_ptr->data_.try_emplace(path, std::make_shared<T>(path)) };

        return std::dynamic_pointer_cast<T>(*emplaced_it);
    }

    template<std::derived_from<IDataResource> T>
    std::shared_ptr<T> load(const std::string& path) {
        auto [emplaced_it, was_emplaced]{ data_.try_emplace(path, std::make_shared<T>(path)) };

        return std::dynamic_pointer_cast<T>(*emplaced_it);
    }
};

#pragma once
#include <memory>
#include <string>
#include "GLHandlePool.h"
#include "DataPool.h"


template<typename G, typename D>
class ResourceCouple {
private:
    std::shared_ptr<G> gl_handle;
    std::shared_ptr<D> heap_data;

    std::shared_ptr<DataPool> data_pool;
    std::shared_ptr<GLHandlePool> handle_pool;
public:
    const std::string name;

    ResourceCouple(const std::string& path_or_name)
            : ResourceCouple(path_or_name, DataPool::singleton(), GLHanlePool::singleton()) {}

    ResourceCouple(const std::string& path_or_name, std::shared_ptr<DataPool> dp, std::shared_ptr<GLHandlePool> hp)
            : name{ path_or_name }, data_pool{ dp }, handle_pool{ hp } {}

    // TODO: implement efficient cross-loading of resources
    std::shared_ptr<G> glhandle() {
        if (!gl_handle) {
            gl_handle = handle_pool->emplace_from_data<G, D>(name, data());
        }
        return gl_handle;
    }

    std::shared_ptr<D> data() {
        if (!heap_data) {
            heap_data = data_pool->load(name);
        }
        return heap_data;
    }
};

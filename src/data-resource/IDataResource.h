#pragma once
#include <string>
#include <utility>

// An interface resource class, that serves as a base for all
// data-like resources: models, textures, shader files, etc.


class IDataResource {
public:
    const std::string path_;

    explicit IDataResource(std::string path) : path_{ std::move(path) } {}

    virtual IDataResource& load() = 0;

    virtual ~IDataResource() = 0;
};

IDataResource::~IDataResource() = default;

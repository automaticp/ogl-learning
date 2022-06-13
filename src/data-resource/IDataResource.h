#pragma once
#include <string>
#include <utility>

// An interface resource class, that serves as a base for all
// data-like resources: models, textures, shader files, etc.

// Existing instance of a class deriving from IDataResource
// must guarantee the existance of the data from the specified path_

class IDataResource {
public:
    const std::string path;

    explicit IDataResource(std::string path) : path{ std::move(path) } {}

    virtual ~IDataResource() = 0;
};

inline IDataResource::~IDataResource() = default;

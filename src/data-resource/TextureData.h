#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <cstddef>
#include <stb_image.h>
#include "IDataResource.h"


class TextureData : public IDataResource  {
public:
    std::vector<unsigned char> data;
    int width;
    int height;
    int num_channels;

    explicit TextureData(const std::string& path) : IDataResource(path) {
        load_texture_data(0);
    }

private:
    void load_texture_data(int num_desired_channels = 0) {
        stbi_set_flip_vertically_on_load(true);
        unsigned char* image_data = stbi_load(path.c_str(), &width, &height, &num_channels, num_desired_channels);

        if ( !image_data ) {
            throw std::runtime_error("Could not read image file at: " + this->path);
        }
        size_t num_bytes{ static_cast<size_t>(width) * height * num_channels };

        data = std::vector<unsigned char>(image_data, image_data + num_bytes);

        stbi_image_free(image_data);
    }

};

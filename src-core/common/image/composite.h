#pragma once

#include <cstdint>
#include "image.h"
#include <string>
#include "nlohmann/json.hpp"

namespace image
{
    // Generate a composite from channels and an equation
    template <typename T>
    Image<T> generate_composite_from_equ(std::vector<Image<T>> inputChannels, std::vector<std::string> channelNumbers, std::string equation, nlohmann::json offsets_cfg, float *progress = nullptr);
}
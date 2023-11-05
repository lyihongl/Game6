#pragma once

#include "resource.hpp"

#include <array>

namespace Constants {
    enum class ResourceIndex : int { WOOD = 0, FOOD = 1 };
    const std::array<Resource, 2> ResourcesMetadata = {
        Resource{"wood"},
        Resource{"food"},
    };

    const Resource &getResource(ResourceIndex i) {
        return ResourcesMetadata[static_cast<int>(i)];
    }

    const std::string getResourceName(ResourceIndex i) {
        return ResourcesMetadata[static_cast<int>(i)].getName();
    }
}; // namespace Constants
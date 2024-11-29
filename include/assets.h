#ifndef BAASSISTANT_ASSETS_H
#define BAASSISTANT_ASSETS_H

#include <filesystem>

namespace Baa {

const std::filesystem::path cwd = std::filesystem::current_path();

const std::filesystem::path assets = cwd / "../assets";

}

#endif  // BAASSISTANT_ASSETS_H

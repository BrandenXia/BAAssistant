#ifndef BAASSISTANT_ASSETS_H
#define BAASSISTANT_ASSETS_H

#include <filesystem>

namespace Baa {

std::filesystem::path cwd = std::filesystem::current_path();

std::filesystem::path assets = cwd / "../assets";

}

#endif  // BAASSISTANT_ASSETS_H

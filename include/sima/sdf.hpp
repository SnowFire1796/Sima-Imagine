#pragma once
#include "sima/geometry.hpp"
#include <filesystem>
namespace sima {
struct Document{std::string name{"untitled"};int canvas_width{256},canvas_height{256};std::string mode{"monochrome"};std::vector<Shape> shapes;};
void save_sdf(const std::filesystem::path&,const Document&); Document load_sdf(const std::filesystem::path&);
}

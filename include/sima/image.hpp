#pragma once
#include <cstdint>
#include <filesystem>
#include <vector>
namespace sima {
struct Image { int width{},height{},channels{1}; std::vector<std::uint8_t> pixels; [[nodiscard]] bool valid() const noexcept; std::uint8_t& at(int x,int y,int c=0); const std::uint8_t& at(int x,int y,int c=0) const; };
[[nodiscard]] Image load_image(const std::filesystem::path&,int requested_channels=1);
void save_png(const std::filesystem::path&,const Image&);
[[nodiscard]] Image resize_image(const Image&,int width,int height);
[[nodiscard]] Image to_grayscale(const Image&);
}

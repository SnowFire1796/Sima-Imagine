#pragma once
#include "sima/sdf.hpp"
namespace sima {
struct RenderOptions{int width{256},height{256},supersampling{3};std::uint64_t seed{1};bool invert{};};
Image render_document(const Document&,const RenderOptions& options = RenderOptions{});
Image generate_from_library(const std::filesystem::path&,const std::string&,const RenderOptions&={});
}

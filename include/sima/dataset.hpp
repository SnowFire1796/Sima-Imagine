#pragma once
#include <filesystem>
#include <vector>
namespace sima {
struct DatasetItem{std::filesystem::path image,mask;};
std::vector<DatasetItem> scan_dataset(const std::filesystem::path&,const std::filesystem::path& masks={});
}

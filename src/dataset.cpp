#include "sima/dataset.hpp"
#include <algorithm>
#include <cctype>
#include <stdexcept>
namespace sima {
std::vector<DatasetItem> scan_dataset(const std::filesystem::path&r,const std::filesystem::path&m){if(!std::filesystem::exists(r))throw std::runtime_error("Dataset directory missing: "+r.string());std::vector<DatasetItem>v;for(auto&e:std::filesystem::recursive_directory_iterator(r)){if(!e.is_regular_file())continue;auto ext=e.path().extension().string();std::transform(ext.begin(),ext.end(),ext.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});if(ext!=".png"&&ext!=".jpg"&&ext!=".jpeg"&&ext!=".bmp"&&ext!=".tga"&&ext!=".ppm")continue;std::filesystem::path mask;if(!m.empty()){auto q=m/(e.path().stem().string()+".png");if(std::filesystem::exists(q))mask=q;}v.push_back({e.path(),mask});}std::sort(v.begin(),v.end(),[](auto&a,auto&b){return a.image.string()<b.image.string();});return v;}
}

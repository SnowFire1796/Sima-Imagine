#pragma once
#include "sima/dataset.hpp"
#include "sima/sdf.hpp"
namespace sima {
struct TrainOptions{std::filesystem::path input,masks,output;std::string category{"object"};int canvas_size{256};std::size_t limit{};};
struct TrainReport{std::size_t discovered{},trained{},skipped{};};
TrainReport train_dataset(const TrainOptions&);
}

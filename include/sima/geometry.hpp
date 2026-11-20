#pragma once
#include "sima/image.hpp"
#include <string>
#include <vector>
namespace sima {
struct Point{double x{},y{};}; struct Rect{double x{},y{},width{},height{};};
struct Shape{std::string type{"polygon"},component{"silhouette"};double x{},y{},width{},height{},rotation{};bool flip_x{},flip_y{};int fill{255},outline{0};double outline_width{2};std::vector<Point> points;};
struct ShapeMatch{std::string type;double confidence{},error{};};
double polygon_area(const std::vector<Point>&); double perimeter(const std::vector<Point>&);
std::vector<Point> convex_hull(std::vector<Point>); std::vector<Point> simplify_contour(const std::vector<Point>&,double);
ShapeMatch classify_shape(const std::vector<Point>&); std::vector<Point> boundary_points(const Image&,std::size_t max_points=1200); Rect bounds_of(const std::vector<Point>&);
}

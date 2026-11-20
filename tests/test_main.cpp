#include "sima/geometry.hpp"
#include "sima/sdf.hpp"
#include "sima/renderer.hpp"
#include <cassert>
#include <cmath>
#include <filesystem>
#include <iostream>
int main(){using namespace sima;std::vector<Point>t{{0,0},{10,0},{5,10}};assert(std::abs(polygon_area(t)-50)<1e-6);assert(classify_shape(t).type=="triangle");auto b=bounds_of(t);assert(b.width==10&&b.height==10);Document d;d.name="test";Shape s;s.type="triangle";s.x=.25;s.y=.25;s.width=.5;s.height=.5;d.shapes.push_back(s);auto p=std::filesystem::temp_directory_path()/"sima-test.sdf";save_sdf(p,d);auto q=load_sdf(p);assert(q.name=="test"&&q.shapes.size()==1);auto im=render_document(q,RenderOptions{64,64,2,1,false});assert(im.valid()&&im.width==64);std::filesystem::remove(p);std::cout<<"Sima tests passed\n";}

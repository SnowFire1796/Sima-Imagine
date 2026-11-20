#include "sima/sdf.hpp"
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <utility>
namespace sima {
void save_sdf(const std::filesystem::path&p,const Document&d){if(!p.parent_path().empty())std::filesystem::create_directories(p.parent_path());std::ofstream f(p);if(!f)throw std::runtime_error("Cannot write SDF");f<<"SIMA_SDF 1\nname "<<std::quoted(d.name)<<"\ncanvas "<<d.canvas_width<<' '<<d.canvas_height<<"\nmode "<<d.mode<<"\nshapes "<<d.shapes.size()<<'\n';for(auto&s:d.shapes){f<<"shape "<<s.type<<' '<<s.component<<' '<<std::setprecision(10)<<s.x<<' '<<s.y<<' '<<s.width<<' '<<s.height<<' '<<s.rotation<<' '<<s.flip_x<<' '<<s.flip_y<<' '<<s.fill<<' '<<s.outline<<' '<<s.outline_width<<' '<<s.points.size();for(auto q:s.points)f<<' '<<q.x<<' '<<q.y;f<<'\n';}}
Document load_sdf(const std::filesystem::path&p){std::ifstream f(p);if(!f)throw std::runtime_error("Cannot read SDF");Document d;std::string magic,k;int v=0;std::size_t count=0;if(!(f>>magic>>v)||magic!="SIMA_SDF"||v!=1)throw std::runtime_error("Unsupported SDF");while(f>>k){if(k=="name")f>>std::quoted(d.name);else if(k=="canvas")f>>d.canvas_width>>d.canvas_height;else if(k=="mode")f>>d.mode;else if(k=="shapes")f>>count;else if(k=="shape"){Shape s;std::size_t n=0;f>>s.type>>s.component>>s.x>>s.y>>s.width>>s.height>>s.rotation>>s.flip_x>>s.flip_y>>s.fill>>s.outline>>s.outline_width>>n;for(std::size_t i=0;i<n;++i){Point q;f>>q.x>>q.y;s.points.push_back(q);}if(!f)throw std::runtime_error("Malformed SDF");d.shapes.push_back(std::move(s));}else throw std::runtime_error("Unknown SDF field "+k);}if(d.shapes.size()!=count)throw std::runtime_error("SDF count mismatch");return d;}
}

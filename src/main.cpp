#include "sima/renderer.hpp"
#include "sima/trainer.hpp"
#include "sima/image.hpp"
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
namespace {
void help(){std::cout<<R"(Sima-Imagine 0.1.0 - C++26 monochrome geometry image experiment
Commands:
 sima train --input DIR --class NAME [--output learned] [--masks DIR] [--size 256] [--limit N]
 sima generate --class NAME [--learned learned] [--output output/result.png] [--size 256] [--seed 1] [--invert]
 sima inspect --file PATH.sdf
 sima help
Masks: image and mask must share a basename; mask label 2 is treated as background.
v0.1 extracts whole-object silhouettes; it does not label semantic parts (eyes/ears/nose).
)";}
std::map<std::string,std::string> args(int n,char**v,int start){std::map<std::string,std::string>a;for(int i=start;i<n;++i){std::string k=v[i];if(k=="--invert"){a[k]="1";continue;}if(!k.starts_with("--")||i+1>=n)throw std::runtime_error("Invalid argument: "+k);a[k]=v[++i];}return a;}
std::string get(const auto&a,const std::string&k,const std::string&d){auto i=a.find(k);return i==a.end()?d:i->second;}
int num(const auto&a,const std::string&k,int d){return std::stoi(get(a,k,std::to_string(d)));}
}
int main(int argc,char**argv){try{if(argc<2){help();return 0;}std::string cmd=argv[1];if(cmd=="help"||cmd=="--help"){help();return 0;}auto a=args(argc,argv,2);
if(cmd=="train"){sima::TrainOptions o;o.input=get(a,"--input","");o.category=get(a,"--class","object");o.output=get(a,"--output","learned");o.masks=get(a,"--masks","");o.canvas_size=num(a,"--size",256);o.limit=static_cast<std::size_t>(num(a,"--limit",0));if(o.input.empty())throw std::runtime_error("train requires --input");auto r=sima::train_dataset(o);std::cout<<"Training finished: "<<r.trained<<" trained, "<<r.skipped<<" skipped of "<<r.discovered<<".\n";return r.trained?0:2;}
if(cmd=="generate"){auto c=get(a,"--class","cat"),root=get(a,"--learned","learned"),out=get(a,"--output","output/result.png");sima::RenderOptions o;o.width=num(a,"--size",256);o.height=o.width;o.seed=std::stoull(get(a,"--seed","1"));o.invert=a.contains("--invert");sima::save_png(out,sima::generate_from_library(root,c,o));std::cout<<"Saved "<<out<<" (grayscale PNG).\n";return 0;}
if(cmd=="inspect"){auto p=get(a,"--file","");if(p.empty())throw std::runtime_error("inspect requires --file");auto d=sima::load_sdf(p);std::cout<<d.name<<" | "<<d.canvas_width<<'x'<<d.canvas_height<<" | "<<d.shapes.size()<<" shapes\n";for(auto&s:d.shapes)std::cout<<s.component<<": "<<s.type<<" at "<<s.x<<','<<s.y<<" size "<<s.width<<'x'<<s.height<<"\n";return 0;}help();return 1;}catch(const std::exception&e){std::cerr<<"Sima error: "<<e.what()<<'\n';return 2;}}

#include "sima/image.hpp"
#include "stb_image.h"
#include "stb_image_write.h"
#include <algorithm>
#include <stdexcept>
namespace sima {
bool Image::valid()const noexcept{return width>0&&height>0&&channels>0&&pixels.size()==static_cast<std::size_t>(width)*height*channels;}
std::uint8_t& Image::at(int x,int y,int c){return pixels.at((static_cast<std::size_t>(y)*width+x)*channels+c);}
const std::uint8_t& Image::at(int x,int y,int c)const{return pixels.at((static_cast<std::size_t>(y)*width+x)*channels+c);}
Image load_image(const std::filesystem::path&p,int req){int w=0,h=0,c=0;auto*d=stbi_load(p.string().c_str(),&w,&h,&c,req);if(!d)throw std::runtime_error("Image load failed: "+p.string());int ch=req?req:c;Image o{w,h,ch,{}};auto n=static_cast<std::size_t>(w)*h*ch;o.pixels.assign(d,d+n);stbi_image_free(d);return o;}
void save_png(const std::filesystem::path&p,const Image&i){if(!i.valid())throw std::runtime_error("Invalid image");if(!p.parent_path().empty())std::filesystem::create_directories(p.parent_path());if(!stbi_write_png(p.string().c_str(),i.width,i.height,i.channels,i.pixels.data(),i.width*i.channels))throw std::runtime_error("PNG write failed");}
Image to_grayscale(const Image&s){if(!s.valid())throw std::runtime_error("Invalid image");if(s.channels==1)return s;Image o{s.width,s.height,1,std::vector<std::uint8_t>(static_cast<std::size_t>(s.width)*s.height)};for(int y=0;y<s.height;++y)for(int x=0;x<s.width;++x){int r=s.at(x,y,0),g=s.at(x,y,std::min(1,s.channels-1)),b=s.at(x,y,std::min(2,s.channels-1));o.at(x,y)=static_cast<std::uint8_t>((299*r+587*g+114*b)/1000);}return o;}
Image resize_image(const Image&s,int w,int h){if(!s.valid()||w<1||h<1)throw std::runtime_error("Invalid resize");Image o{w,h,s.channels,std::vector<std::uint8_t>(static_cast<std::size_t>(w)*h*s.channels)};for(int y=0;y<h;++y)for(int x=0;x<w;++x){double sx=(x+.5)*s.width/w-.5,sy=(y+.5)*s.height/h-.5;int x0=std::clamp(static_cast<int>(sx),0,s.width-1),y0=std::clamp(static_cast<int>(sy),0,s.height-1),x1=std::min(x0+1,s.width-1),y1=std::min(y0+1,s.height-1);double fx=std::clamp(sx-x0,0.0,1.0),fy=std::clamp(sy-y0,0.0,1.0);for(int c=0;c<s.channels;++c){double a=s.at(x0,y0,c)*(1-fx)+s.at(x1,y0,c)*fx,b=s.at(x0,y1,c)*(1-fx)+s.at(x1,y1,c)*fx;o.at(x,y,c)=static_cast<std::uint8_t>(std::clamp(a*(1-fy)+b*fy,0.0,255.0));}}return o;}
}

#ifndef K2_ENGINE_VERTEX_HPP_
#define K2_ENGINE_VERTEX_HPP_

#include "../k2_math/vector4.hpp"
#include <fstream>

namespace k2_engine{

class Vertex{
        k2_math::Vec4<float> pos; 
        k2_math::Vec4<unsigned char> rgba;
        float illumination;

public:
        Vertex()
                : pos(k2_math::Vec4<float>()), rgba(k2_math::Vec4<unsigned char>()), illumination(0) {}
        Vertex(const Vertex& vx)
                : pos(vx.pos), rgba(vx.rgba), illumination(vx.illumination) {}

        Vertex(const k2_math::Vec4<float>& pos, const k2_math::Vec4<unsigned char>& rgba, float illumination = 0)
                : pos(pos), rgba(rgba), illumination(illumination){}

        Vertex(const k2_math::Vec4<float>& pos)
                : pos(pos), rgba(k2_math::Vec4<unsigned char>()), illumination(0){}

        k2_math::Vec4<float> get_pos() const { return pos; }
        k2_math::Vec4<float>& ref_pos() { return pos; }
        void set_pos(const k2_math::Vec4<float>& new_pos) { pos = new_pos; }
        
        k2_math::Vec4<unsigned char> get_rgba() const { return rgba; }
        k2_math::Vec4<unsigned char>& ref_rgba() { return rgba; }
        void set_rgba(const k2_math::Vec4<unsigned char>& new_rgba) { rgba = new_rgba; }

        float get_x() const{ return pos.get_x(); }
        float get_y() const{ return pos.get_y(); }
        float get_z() const{ return pos.get_z(); }

        friend std::ofstream& operator<<(std::ofstream& os, const Vertex& vertex);
        friend std::ifstream& operator>>(std::ifstream& is, Vertex& vertex);
};

}

#endif // K2_ENGINE_VERTEX_HPP_
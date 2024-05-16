#ifndef K2_ENGINE_RENDERER_HPP_
#define K2_ENGINE_RENDERER_HPP_

#include "vertex.hpp"
#include "triangle.hpp"
#include "world_elements.hpp"
#include "gamespace.hpp"
#include "../k2_math/matrix4.hpp"
#include "../../dep/output.hpp"
#include "../../dep/utils.hpp"
#include "../k2_math/basic_algorithms.hpp"
#include <vector>
#include <iostream>

namespace k2_engine{


class Renderer{
        const GameSpace* scene;
        std::vector<Triangle> wiremesh;
        outp::OutputBuffer output_buffer;
        size_t window_width;
        size_t window_height;
        k2_math::Vec4<float> bg_centre_2d;
        float render_distance;


        void draw_line(const Vertex&, const Vertex&);

public:
        Renderer(const GameSpace& scene, size_t window_width, size_t window_height, float render_distance = 50)
                : scene(&scene), output_buffer(outp::OutputBuffer(window_width, window_height)),
                  window_width(window_width), window_height(window_height), render_distance(render_distance){}
        void extract_wiremesh();
        void illuminate();
        void cull();
        void view_transform();
        void project();
        void draw_wireframe(); //Debug miatt
        void rasterize();
        void draw_background();
        void draw();        
        void render();

};

}//namespace
#endif //K2_ENGINE_RENDERER_HPP_
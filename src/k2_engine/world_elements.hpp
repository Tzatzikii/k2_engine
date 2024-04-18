#ifndef K2_ENGINE_GAME_OBJECTS_HPP_
#define K2_ENGINE_GAME_OBJECTS_HPP_
#include <vector>
#include <memory>
#include <iostream>
#include "triangle.hpp"
#include "../k2_math/vector4.hpp"
#include "../k2_math/matrix4.hpp"
#include "shapes.hpp"
namespace k2_engine{

class WorldElement{
public:
        virtual ~WorldElement() = default;
};

class Object : public WorldElement{
protected:
        Shape* shape;

public:
        Object(Shape* shape) : shape(shape) {}
        Shape get_shape() const  { std::cout << "aa\n"; return *shape;   }
        ~Object(){delete shape;}

};

class DynamicObject : public Object{
        int tickrate;

public:
        DynamicObject(Shape* shape) : Object(shape){}
        virtual void step() = 0;

};


class StaticObject : public Object{

public:
        StaticObject(Shape* shape) : Object(shape){}
        
};

class LightSource : public WorldElement{
protected:
        float brightness;
        float range;
};

class Camera : public WorldElement{
        float radius;
        k2_math::Vec4<float> pos;
        k2_math::Vec4<float> rot;
        
public:
        Camera(float x = 0, float y = 0, float z = 0, float r = 10, float rotx = 0, float rotz = 0, float roty = 0)
                : pos(k2_math::Vec4<float>(x, y, z)), rot(k2_math::Vec4<float>(rotx, roty, rotz)), radius(r){}

        float get_radius() const { return radius; }
        k2_math::Vec4<float> get_rot() const{ return rot; }
        k2_math::Vec4<float> get_pos() const{ return pos; }
        k2_math::Vec4<float>& ref_pos() { return pos; }
        k2_math::Vec4<float>& ref_rot() { return rot; }
        void rotate(float dx, float dy, float dz){
                rot += k2_math::Vec4<float>(dx, dy, dz);
        }
        void translate(float dx, float dy, float dz){
                k2_math::Vec4<float> d(dx, dy, dz);
                pos +=  k2_math::Mat4<float>::rotation(rot) * d;
        }

        Camera(const Camera&) = delete;
        Camera& operator=(const Camera&) = delete;
};



}

#endif //K2_ENGINE_GAME_OBJECTS_HPP_
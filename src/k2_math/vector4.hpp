#ifndef K2_MATH_VECTOR4_HPP_
#define K2_MATH_VECTOR4_HPP_

#include <cmath>

namespace k2_math {
 

template <typename T>
class Vec4{

protected:
        T x;
        T y;
        T z;
        T w;

public:
        Vec4(T x = 0, T y = 0, T z = 0, T w = 0)
                :x(x), y(y), z(z), w(w){}
        
        const T get_x() const {return x;}
        const T get_y() const {return y;}
        const T get_z() const {return z;}
        const T get_w() const {return w;}
        void set_x(T new_x) {x = new_x;}
        void set_y(T new_y) {y = new_y;}
        void set_z(T new_z) {z = new_z;}
        void set_w(T new_w) {w = new_w;}
        Vec4<T> operator+(const Vec4<T>& rhs_v) const{
                return Vec4<T>(x+rhs_v.x, y+rhs_v.y, z+rhs_v.z, w+rhs_v.w);
        }
        
        Vec4<T>& operator+=(const Vec4<T>& rhs_v){
                (*this) = (*this) + rhs_v;
                return (*this);
        }

        Vec4<T> operator*(const Vec4<T> rhs_v){
                return Vec4<T>(x*rhs_v.x, y*rhs_v.y, z*rhs_v.z, w*rhs_v.w);
        }

        Vec4<T>& operator*=(const Vec4<T>& rhs_v){
                (*this) = (*this)*rhs_v;
                return (*this);
        }

        Vec4<T> operator*(T rhs_n) const {
                return Vec4<T>(x*rhs_n, y*rhs_n, z*rhs_n, w*rhs_n);
        }
        
        Vec4<T>& operator*=(T rhs_n){
                (*this) = (*this)*rhs_n;
                return *this;
        }
        Vec4<T> operator-(const Vec4<T>& rhs_v) const{
                Vec4<T> A(x, y, z, w); 
                Vec4<T> B(rhs_v);
                return Vec4<T>(A+(B*(-1)));
        }
        
        Vec4<T>& operator-=(const Vec4<T>& rhs_v){
                (*this) = (*this) - rhs_v;
                return (*this);
        } 
        Vec4<T> operator/(T n) const{
                return Vec4<T>(x/n, y/n, z/n, w/n);
        }
        Vec4<T> operator/=(T n){
                return (*this)/n;
        }
        
};

} //namespace k2_math
#endif // K2_MATH_VECTOR4_HPP_
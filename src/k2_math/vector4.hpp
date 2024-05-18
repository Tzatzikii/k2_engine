#ifndef K2_MATH_VECTOR4_HPP_
#define K2_MATH_VECTOR4_HPP_

#include <cmath>
#include <fstream>

namespace k2_math {
 

template <typename T>
class Vec4{

protected:
        T x;
        T y;
        T z;
        T w;

public:
        Vec4(T x = 0, T y = 0, T z = 0, T w = 1)
                :x(x), y(y), z(z), w(w){}
        
        const T get_x() const {return x;}
        const T get_y() const {return y;}
        const T get_z() const {return z;}
        const T get_w() const {return w;}
        void set_x(T new_x) {x = new_x;}
        void set_y(T new_y) {y = new_y;}
        void set_z(T new_z) {z = new_z;}
        void set_w(T new_w) {w = new_w;}
        void len3d() { return std::cbrt(x*x*x + y*y*y + z*z*z);}
        Vec4<T> operator+(const Vec4<T>& rhs_v) const{
                return Vec4<T>(x+rhs_v.x, y+rhs_v.y, z+rhs_v.z, w+rhs_v.w);
        }
        
        Vec4<T>& operator+=(const Vec4<T>& rhs_v){
                (*this) = (*this) + rhs_v;
                return (*this);
        }


        Vec4<T>& operator*=(const Vec4<T>& rhs_v){
                (*this) = (*this)*rhs_v;
                return (*this);
        }

        Vec4<T> operator*(const T& rhs_n) const {
                return Vec4<T>(x*rhs_n, y*rhs_n, z*rhs_n, w*rhs_n);
        }
        
        Vec4<T>& operator*=(const T& rhs_n){
                (*this) = (*this)*rhs_n;
                return *this;
        }
        Vec4<T> operator/(T n) const{
                return Vec4<T>(x/n, y/n, z/n, w/n);
        }
        Vec4<T> operator/=(T n){
                return (*this)/n;
        }

        Vec4<T> operator-() const{
                Vec4<T> neg = *this;
                neg*=-1;
                return neg;
        }
        Vec4<T> operator-(const Vec4<T>& rhs_v) const{
                Vec4<T> A(x, y, z, w); 
                Vec4<T> B(rhs_v);
                return Vec4<T>(A+(-B));
        }
        
        Vec4<T>& operator-=(const Vec4<T>& rhs_v){
                (*this) = (*this) - rhs_v;
                return (*this);
        } 

        friend std::ofstream& operator<<(std::ofstream& os, const Vec4<T>& vector){

                os<<'['<<vector.x<<':'<<vector.y<<':'<<vector.z<<':'<<vector.w<<']';
                return os;
        }
        friend std::ifstream& operator>>(std::ifstream& is, Vec4<T>& vector){
                T x, y, z, w;
                ((((is.ignore(1, '[')>>x).ignore(1, ':')>>y).ignore(1, ':')>>z).ignore(1, ':')>>w).ignore(1, ']');
                vector.set_x(x); vector.set_y(y); vector.set_z(z); vector.set_w(w);
                return is;
        }
        
};


} //namespace k2_math
#endif // K2_MATH_VECTOR4_HPP_
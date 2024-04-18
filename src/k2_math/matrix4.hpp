#ifndef K2_MATH_MATRIX4_HPP_
#define K2_MATH_MATRIX4_HPP_

#include <cstring>
#include <cmath>
#include "vector4.hpp"
#include "../../dep/utils.hpp"
#include "../../dep/output.hpp"

#define BEGIN_MATRIX_ITERATOR for(int i = 0; i < 4; i++){ \
                                for(int j = 0; j < 4; j++){
#define END_MATRIX_ITERATOR }}

namespace k2_math{

template <typename T>
class Vec4;

template <typename T>
class Mat4{
        T matrix[4][4];

public:
        Mat4<T>(): matrix{{1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 1}}{}
        const auto get_matrix() const{
                return matrix;
        }
        static Mat4<T> null(){

                Mat4<T> m;
                
                m.matrix[0][0] = 0;
                m.matrix[1][1] = 0;
                m.matrix[2][2] = 0;
                m.matrix[3][3] = 0;
                
                return m;
        }

        static Mat4<T> translation(const Vec4<T>& v){
                Mat4<T> m;

                m.matrix[0][3] = v.get_x();
                m.matrix[1][3] = v.get_y();
                m.matrix[2][3] = v.get_z();
                
                return m;
        }
        static Mat4<float> rotation_x(float th) {
                Mat4<float> m;

                m.matrix[1][1] = cos(th);
                m.matrix[1][2] = -sin(th);
                m.matrix[2][1] = sin(th);
                m.matrix[2][2] = cos(th);
                
                return m;
        }
        
        static Mat4<float> rotation_y(float th){
                Mat4<float> m;
                
                m.matrix[0][0] = cos(th);
                m.matrix[0][2] = sin(th);
                m.matrix[2][0] = -sin(th);
                m.matrix[2][2] = cos(th);

                return m;
        }

        static Mat4<float> rotation_z(float th){
                Mat4<float> m;

                m.matrix[0][0] = cos(th);
                m.matrix[0][1] = -sin(th);
                m.matrix[1][0] = sin(th);
                m.matrix[1][1] = cos(th);
                
                return m;
        }

        
        static Mat4<float> inverse_rotation(const Mat4<float> m){
                Mat4<float> inv;
                for(int i = 0; i < 4; i++){
                        for(int j = 0; j < 4; j++){
                                inv.matrix[j][i] = m.matrix[i][j];
                        }
                }
                return inv;
        }

        static Mat4<T> inverse_translation(const Mat4<T> m){
                Mat4<T> inv = m;
                inv.matrix[0][3]*=-1;
                inv.matrix[1][3]*=-1;
                inv.matrix[2][3]*=-1;

                return inv;
        }

        static Mat4<T> projection(const Vec4<T>& screen){
                Mat4<T> proj;
                proj.matrix[0][2] = (screen.get_x()/2)/screen.get_z();
                proj.matrix[1][2] = (screen.get_y()/2)/screen.get_z();
                proj.matrix[2][2] = 1/screen.get_z();
                
                return proj;
        }

        Mat4<T> operator+(const Mat4<T>& rhs_m) const{
                Mat4<T> m;

                for(int i = 0; i < 4; i++){
                        for(int j = 0; j < 4; j++){
                                m[i][j] = matrix[i][j] + rhs_m.matrix[i][j];
                        }
                }
                
                return m;
        }

        Mat4<T> operator*(const Mat4<T>& rhs_m) const{
                Mat4<T> m = Mat4<T>::null();

                for(int i = 0; i < 4; i++){
                        for(int j = 0; j < 4; j++){
                                for(int k = 0; k < 4; k++){
                                        m.matrix[i][j] += matrix[i][k]*rhs_m.matrix[k][j];
                                        
                                }
                        }
                }
                return m;
        }
        
        Mat4<T>& operator*=(const Mat4<T>& rhs_m){
                (*this) = (*this) * rhs_m;

                return (*this);
        }
        
        Mat4<T>& operator+=(const Mat4<T>& rhs_m){
                *this = *this + rhs_m;

                return *this;
        }

        Vec4<T> operator*(const Vec4<T>& rhs_v) const{
                Vec4<T> v;

                v.set_x(rhs_v.get_x()*matrix[0][0] + rhs_v.get_y()*matrix[0][1] + rhs_v.get_z()*matrix[0][2] + rhs_v.get_w()*matrix[0][3]);
                v.set_y(rhs_v.get_x()*matrix[1][0] + rhs_v.get_y()*matrix[1][1] + rhs_v.get_z()*matrix[1][2] + rhs_v.get_w()*matrix[1][3]);
                v.set_z(rhs_v.get_x()*matrix[2][0] + rhs_v.get_y()*matrix[2][1] + rhs_v.get_z()*matrix[2][2] + rhs_v.get_w()*matrix[2][3]);
                v.set_w(rhs_v.get_x()*matrix[3][0] + rhs_v.get_y()*matrix[3][1] + rhs_v.get_z()*matrix[3][2] + rhs_v.get_w()*matrix[3][3]);
                
                return v;
        }

        Mat4<T> operator*(T n) const{
                Mat4<T> m;
                for(int i = 0; i < 4; i++){
                        for(int j = 0; j < 4; j++){
                                m.matrix[i][j]*=n;
                        }
                }
                return m;
        } 
        Mat4<T>& operator*=(T n){
                (*this) = (*this) * n;
                return (*this);
        }
        Mat4<T> operator/(T n) const{
                const Mat4<T> m = *this;
                return Mat4<T>(m*(1/n));
        }
        Vec4<T>& operator*=(Vec4<T>& rhs_v){
                rhs_v = (*this) * rhs_v;
                return rhs_v;
        }

        static Mat4<float> rotation(const Vec4<float>& rotation){
                Mat4<float> m = (Mat4<float>::rotation_x(rotation.get_x())*
                                Mat4<float>::rotation_y(rotation.get_y()))*
                                Mat4<float>::rotation_z(rotation.get_z());
                return m;
        }
        static Mat4<float> rotation(float th_x, float th_y, float th_z){
                Mat4<float> m = Mat4<float>::rotation_x(th_x)*
                                Mat4<float>::rotation_y(th_y)*
                                Mat4<float>::rotation_z(th_z);
                return m;
        }
};

} //namespace k2_math

#endif // K2_MATH_MATRIX4_HPP_
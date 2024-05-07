
#include "logics_module_test.hpp"
using namespace k2_math;
const float PI = 3.1415926535;

// Az elvart ertekeket egy online matrix muveletekre kepes szamologeppel hataroztam meg, lehetoleg
// minel veletlenszerubb szamokat hasznaltam
void start_gtest(){
        TEST(Matrix, IdentityCtor)
                Mat4<int> int_m;
                int expected[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
                // Ha int-el jól viselkedik, a float-tal sem lesz baj,
                // de később az is tesztelve van indirekt módon
                EXPECT_EQ(0, memcmp(int_m.get_matrix(), expected, sizeof(int)*16)) << "Identity matrix ctor error" << std::endl;
        END
        TEST(Matrix, ScalarMultiply)
                Mat4<int> int_m;
                int_m = int_m * 1000;
                int expected[4][4] = {{1000,0,0,0},{0,1000,0,0},{0,0,1000,0},{0,0,0,1000}};
                BEGIN_MATRIX_ITERATOR
                        EXPECT_EQ(expected[i][j], int_m.get_matrix()[i][j]) << "Matrix-Scalar multiplication failed" << std::endl;
                END_MATRIX_ITERATOR
        END
        TEST(Matrix, VectroMultiply)
                Vec4<float> float_v(0.4444, 3.214, 98,43);
                Mat4<float> float_m = Mat4<float>::translation(float_v);
                Vec4<float> float_nullv;
                float_nullv = float_m * float_nullv;
                EXPECT_FLOAT_EQ(float_v.get_x(), float_nullv.get_x());
                EXPECT_FLOAT_EQ(float_v.get_y(), float_nullv.get_y());
                EXPECT_FLOAT_EQ(float_v.get_y(), float_nullv.get_y());
        END
        TEST(Matrix, MatrixMultiply)
                Mat4<float> float_m;
                Mat4<float> translation = Mat4<float>::translation(Vec4<float>(4, 3, 2));
                float_m = float_m*translation;
                BEGIN_MATRIX_ITERATOR
                        EXPECT_FLOAT_EQ(translation.get_matrix()[i][j], float_m.get_matrix()[i][j]) << "Matrix-Matrix multiplication failed at: i= " << i << " j= " << j << std::endl;
                END_MATRIX_ITERATOR
        END
        TEST(Matrix, Translation){
                Mat4<int> int_m = Mat4<int>::translation(Vec4<int>(4, 4, 5));
                int expected[4][4] = {{1,0,0,4},{0,1,0,4},{0,0,1,5},{0,0,0,1}};
                BEGIN_MATRIX_ITERATOR
                        EXPECT_EQ(expected[i][j], int_m.get_matrix()[i][j]) << "Matrix translation failed" << std::endl;; 
                END_MATRIX_ITERATOR
        }
        END
        TEST(Matrix, RotationX)
                Mat4<float> rot_x_m = Mat4<float>::rotation_x(15*PI/180); //~15° 
                float expected[4][4] = {{1,0,0,0},{0,0.965925,-0.258819,0},{0,0.258819,0.965925,0},{0,0,0,1}}; 
                BEGIN_MATRIX_ITERATOR
                        EXPECT_FLOAT_EQ(expected[i][j], rot_x_m.get_matrix()[i][j]);
                END_MATRIX_ITERATOR 
        END
        TEST(Matrix, RotationY)
                Mat4<float> rot_y_m = Mat4<float>::rotation_y(31*PI/180); //~31°
                float expected[4][4] = {{0.857167,0,0.515038,0},{0,1,0,0},{-0.515038,0,0.857167,0},{0,0,0,1}};
                BEGIN_MATRIX_ITERATOR
                        EXPECT_FLOAT_EQ(expected[i][j], rot_y_m.get_matrix()[i][j]);
                END_MATRIX_ITERATOR
        END
        TEST(Matrix, RotationZ)
                Mat4<float> rot_z_m = Mat4<float>::rotation_z(18.36*PI/180); //~18.36°
                float expected[4][4] = {{0.949096,-0.314986,0,0},{0.314986,0.949096,0,0},{0,0,1,0},{0,0,0,1}};
                BEGIN_MATRIX_ITERATOR
                        EXPECT_FLOAT_EQ(expected[i][j], rot_z_m.get_matrix()[i][j]);
                END_MATRIX_ITERATOR
        END
        TEST(Matrix, InverseRotation)
                Mat4<float> rot_x_m = Mat4<float>::rotation_x(31*PI/180);
                float expected[4][4] = {{1,0,0,0},{0,0.857167,0.515038,0},{0,-0.515038,0.857167,0},{0,0,0,1}};
                BEGIN_MATRIX_ITERATOR
                        EXPECT_FLOAT_EQ(expected[i][j], rot_x_m.get_matrix()[i][j]);
                END_MATRIX_ITERATOR
        END
        TEST(Intersection, ZLine)
                Vec4<float> A(3, 4, 5);
                Vec4<float> B(-1, 3.4, 2.21);
                Vec4<float> C(-2, -4, -1.2);
                // AB nem metszi, a programban nem fordul elő, hogy
                // ilyenkor metszéspontot kéne keresni
                Vec4<float> CA_z2 = intersect_line(C, A, 2);
                Vec4<float> BC_z2 = intersect_line(B, C, 2);
                EXPECT_FLOAT_EQ(0.58F, roundto<2>(CA_z2.get_x()));
                EXPECT_FLOAT_EQ(0.13F, roundto<2>(CA_z2.get_y()));
                EXPECT_FLOAT_EQ(-1.06F, roundto<2>(BC_z2.get_x()));
                EXPECT_FLOAT_EQ(2.94F, roundto<2>(BC_z2.get_y()));
        END

}


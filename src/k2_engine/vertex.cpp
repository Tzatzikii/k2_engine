#include "vertex.hpp"

namespace k2_engine{

std::ofstream& operator<<(std::ofstream& os, const Vertex& vertex){
        os<<vertex.pos<<vertex.rgba; 
        return os;
}
std::ifstream& operator>>(std::ifstream& is, Vertex& vertex){
        is>>vertex.pos>>vertex.rgba;
        return is;
}
}
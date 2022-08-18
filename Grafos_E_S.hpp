#include ".\Grafo.hpp"
#include ".\GrafoP.hpp"
#include ".\matriz.hpp"
#include<iostream>
//Salida
template <typename tCoste>
std::ostream& operator <<(std::ostream& os, const GrafoP<tCoste> g){
    os << "\t";
    for(size_t i=0; i<g.numVert(); ++i)
        os << i << "\t";
    os << "\n\n";
    for(size_t i=0; i<g.numVert(); ++i){
        os << i << "\t";
        for(size_t j=0; j<g.numVert(); ++j)
            if(g[i][j] == GrafoP<tCoste>::INFINITO)
                os << char(126) << "\t";
            else
                os << g[i][j] << "\t";
        os << "\n\n";
    }
    return os;
}
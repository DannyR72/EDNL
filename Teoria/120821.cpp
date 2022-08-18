#include "..\Implementaciones\Grafo.hpp"
#include "..\Implementaciones\GrafoP.hpp"

void f()
{
    Grafo p(5); //No ponderados (Matriz de adyacencia)
    GrafoP<int> G(5); //ponderados (Matriz de costes)

    p[1][4]=true;

    G[0][3]=100;

    if(G[0][1]==GrafoP<int>::INFINITO)
        cout << "No hay camino entre 0 y 1";





}

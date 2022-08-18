#include "..\Implementaciones\Grafo.hpp"

Grafo G(5); //Declara un grafo no ponderado

G[0][4]=true;
G[3][2]=true;
if(!G[1][0])
    cout << "no hay camino entre 1 y 0";

GrafoP<int> GP(5);

GP[0][3]=100;
GP[3][1]=10;
if(GP[3][2]==GrafoP<int>::INFINITO)



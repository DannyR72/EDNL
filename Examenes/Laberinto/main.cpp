#include<iostream>
#include ".\Laberinto.hpp"

int main()
{
    matriz<bool> tablero(3);
    std::vector<tPared> paredes;
    tPared pared(tCasilla(0,0),tCasilla(0,1));
    paredes.push_back(pared);
    pared.c1=tCasilla(1,1);
    pared.c2=tCasilla(1,2);
    paredes.push_back(pared);

    tCasilla salida(0,0);
    tCasilla llegada(2,2);

    int coste=laberinto<int>(tablero, paredes, salida,llegada);
    std::cout << coste << std::endl;

    return 0;
}
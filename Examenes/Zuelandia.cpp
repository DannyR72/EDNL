#include "..\Implementaciones\matriz.hpp"
#include "..\Implementaciones\GrafoP.hpp"
#include "..\Implementaciones\Floyd.hpp"
#include<vector>

template<typename tCoste>
struct carretera
{
    GrafoP<tCoste>::vertice nodoi, nodoj;
};

template<typename tCoste>
matriz<tCoste> zuelandia(GrafoP<tCoste> G, std::vector<bool> ciudadesBloqueadas, std::vector<carretera<tCoste>> carreteras,
typename GrafoP<tCoste>::vertice capital)
{
    //Cortar todas las carreteras que pasan por las ciudades tomadas


    //cortar las carreteras bloquedas
    for(size_t i=0;i<carreteras.size();++i)
        G[carreteras[i].nodoi][carreteras[i].nodoj]=GrafoP<tCoste>::INFINITO;


    //i--->j  i--->capital---->j
    for(size_t i=0;i<G.numVert();++i)
    {
        for(size_t j=0;j<G.numVert();++j)
        {
            if(G[i][capital]==GrafoP<tCoste>::INFINITO || G[capital][j]==GrafoP<tCoste>::INFINITO)
                G[i][j]=GrafoP<tCoste>::INFINITO;
        }
    }

    //Calcular la matriz de floyd
    matriz<typename GrafoP<tCoste>::vertice> caminos;
    matriz<tCoste> costes=Floyd(G, caminos);

    return costes;
}

/*

  0 1 2 3 4 5 
0 0 - 5 - - -
1 - - - - - -
2
3
4
5

*/
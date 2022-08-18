#include "..\Implementaciones\matriz.hpp"
#include "..\Implementaciones\GrafoP.hpp"
#include "..\Implementaciones\Floyd.hpp"

template<typename tCoste>
struct costes
{
    tCoste coste;
    GrafoP<tCoste>::vertice origen, destino;
};

template<typename tCoste>
costes otravez(GrafoP<tCoste> G)
{
    tCoste costeMin;
    matriz<typename GrafoP<tCoste>::vertice> caminos;

    GrafoP<tCoste> G_aux=invertir(G);

    matriz<tCoste> c=Floyd(G_aux, caminos);

    costeMin=c[0][0];

    typename GrafoP<tCoste>::vertice o, d;
    for(size_t i=0;i<c.dimension();i++)
    {
        for(size_t j=0;j<c.dimension();++j)
        {
            if(c[i][j]<costeMin)
            {
                costeMin=c[i][j];
                o=i;
                d=j;
            }
        }
    }
    costes resultado;
    resultado.coste=(-1)*costeMin;
    resultado.origen=o;
    resultado.destino=d;

    return resultado;
}

 -1 -3 -5 -6 -7
 -2 -4 -5 -6 -7

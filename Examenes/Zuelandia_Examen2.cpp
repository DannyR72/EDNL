#include "Particion.hpp"
#include "..\..\Implementaciones\Kruskal.hpp"
#include "GrafoP.hpp"
#include "matriz.hpp"
#include "Floyd.hpp"
#include <math.h>
template<typename tCoste>
tCoste Grecoland_Huracan(std::vector<tipo_coordenada> ciudades_Fobos, std::vector<tipo_coordenada> ciudades_Deimos,
std::vector<typename GrafoP<tCoste>::vertice> costeras_Fobos, std::vector<typename GrafoP<tCoste>::vertice> costeras_Deimos,
 const Grafo& ady_Fobos, const Grafo& ady_Deimos)
 {
    tCoste puente=GrafoP<tCoste>::INFINITO;
    typename GrafoP<tCoste>::vertice c1, c2; //Ciudades que enlaza el puente

    //Creamos los grafos de fobos y deimos
    GrafoP<tCoste> gFobos(ciudades_Fobos.size());
    GrafoP<tCoste> gDeimos(ciudades_Deimos.size());
    
    for(size_t i=0;i<gFobos.numVert();++i)
    {
        for(size_t j=0;j<gFobos.numVert();++j)
        {
            if(ady_Fobos[i][j])
                gFobos[i][j]=distancia(ciudades_Fobos[i], ciudades_Fobos[j]);
        }
    }
    for(size_t i=0;i<gDeimos.numVert();++i)
    {
        for(size_t j=0;j<gDeimos.numVert();++j)
        {
            if(ady_Deimos[i][j])
                gDeimos[i][j]=distancia(ciudades_Deimos[i], ciudades_Deimos[j]);
        }
    }
    //Creamos los caminos minimos que unen las ciudades
    GrafoP<tCoste> Fobos=Kruskal(gFobos);
    GrafoP<tCoste> Deimos=Kruskal(Deimos);

    //Calculamos cual es el puente mas barato
    for(size_t i=0;i<costeras_Fobos.size();++i)
    {
        for(size_t j=0;j<costeras_Deimos.size();++j)
        {
            if(distancia(ciudades_Fobos[i],ciudades_Deimos[j])<puente)
            {
                puente=distancia(ciudades_Fobos[i],ciudades_Deimos[j]);
                c1=i;
                c2=j;
            }
        }
    }
    cout << "El puente une las ciudades " << c1 << " y " << c2 << endl;
 }
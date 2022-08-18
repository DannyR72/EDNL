#include "..\Implementaciones\Grafo.hpp"
#include "..\Implementaciones\GrafoP.hpp"
#include "..\Implementaciones\Dijkstra.hpp"
#include "..\Implementaciones\Floyd.hpp"
#include "..\Implementaciones\Warshall.hpp"
#include "..\Implementaciones\Kruskal.hpp"
#include "..\Implementaciones\Prim.hpp"
#include "..\Implementaciones\particion.hpp"
#include "..\Implementaciones\particion_vpertenencia.hpp"
#include "..\Implementaciones\Grafos_E_S.hpp"

template<typename T>
T& pruebaDijkstra(const GrafoP<T>& g, typename GrafoP<T>::vertice origen,typename GrafoP<T>::vertice destino)
{
    //Dado un grafo se trata de averiguar cual es el camino menos costoso
    //de un vertice origen a un vertice destino
    std::vector<typename GrafoP<T>::vertice> caminos; //vector de vertices necesario para que dijkstra devuelva los caminos
    std::vector<T> costes; //vector de costes necesario para que dijkstra devuelva los costes minimos de origen al resto de vertices
    costes=Dijkstra(g, origen, caminos);
    return costes[destino];
}

int main()
{
    GrafoP<int> G(5);
    G[0][1]=10;
    G[1][0]=10;
    G[2][3]=20;
    G[4][0]=100;
    G[3][1]=20;
    std::cout << G << std::endl;
    matriz<int> costes;
    matriz<typename GrafoP<int>::vertice> caminos;
    costes=Floyd(G, caminos);
    std::cout << "Matriz de Floyd" << std::endl;
    std::cout << costes << std::endl;
}
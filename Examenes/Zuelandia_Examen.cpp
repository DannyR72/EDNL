/*
La capital de Zuelandia esta alcanzando niveles de toxicidad muy elevados, por ello se ha decretado el cierre a la
ciudad como paso de transito hacia otras ciudades (Para ir de una ciudad a otra no se podra pasar por C. Zuelandia
 pero sí se podrá ir si es residente de la misma empleandola como ciudad destino u origen)

 Implemente un subprograma que dada la capital y un grafo ponderado con los kilometros de las carreteras existentes 
 entre las ciudades del pais, nos devuelva los caminos resultantes de nuestra nueva politica "Sin pasar por la 
 capital, por favor"

*/

#include "..\Implementaciones\GrafoP.hpp"
#include "..\Implementaciones\Floyd.hpp"
#include "..\Implementaciones\matriz.hpp"
template<typename T>
matriz<T> caminos(const GrafoP<T>& g, typename GrafoP<T>::vertice capital)
{
    matriz<GrafoP<T>::vertice> P;
    matriz<T> costes=Floyd(g, P);
    GrafoP<T>::vertice i,j;

    /*
    Posibilidades:
        camino directo entre 2 ciudades y ninguna es la capital: el camino no se modifica
        camino directo entre 2 ciudades y una es la capital: el camino no se modifica
        camino indirecto entre 2 ciudades y una es la capital: el camino no se modifica
        camino indirecto entre 2 ciudades , ninguna es la capital y la capital no esta involucrada en el camino: no se modifica
        camino indirecto entre 2 ciudades, ninguna es la capital y esta está involucrada: SE MODIFICA
        
    */
    for(i=0;i<g.numVert();++i)
    {
        for(j=0;j<g.numVert();++j)
        {
            if(costes[i][capital]!=GrafoP<T>::INFINITO && costes[capital][j]!=GrafoP<T>::INFINITO) //Camino prohibido
                costes[i][j]=GrafoP<T>::INFINITO;
        }
    }
    return costes;
}

int main()
{
    GrafoP<int> g;
    g[0][0]=GrafoP<int>::INFINITO;
    g[0][1]=20;
    g[0][2]=5;
    g[0][3]=10;
    g[0][4]=GrafoP<int>::INFINITO;
    g[1][1]=GrafoP<int>::INFINITO;
    g[2][2]=GrafoP<int>::INFINITO;
    g[3][3]=GrafoP<int>::INFINITO;
    g[4][4]=GrafoP<int>::INFINITO;
    g[1][3]=GrafoP<int>::INFINITO;
    g[3][1]=GrafoP<int>::INFINITO;
    g[4][0]=GrafoP<int>::INFINITO;

    g[1][0]=20;
    g[1][2]=10;
    g[1][4]=25;
    g[2][0]=5;
    g[2][1]=10;
    g[2][3]=10;
    g[2][4]=5;
    g[3][0]=10;
    g[3][2]=10;
    g[3][4]=20;
    g[4][1]=25;
    g[4][2]=5;
    g[4][3]=20;

    caminos(g,2);
}
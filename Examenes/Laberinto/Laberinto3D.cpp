#include "matriz.hpp"
#include "GrafoP.hpp"
#include "Floyd.hpp"
#include<math.h>
#include<vector>

struct tCasilla3D
{
    int i,j,k;
    tCasilla3D(int i, int j, int k): i(i), j(j), k(k){}
};
struct tPared3D
{
    tCasilla3D c1, c2;
};
template<typename T>
typename GrafoP<T>::vertice convertToNodo3D(const tCasilla3D c, int N)
{
	return nodo(c.i*N+c.j+pow(N,2)*c.k);
}
/*
casilla (2,2,0) ---> (2*3+2+pow(N,2)*0) = 8

casilla(2,2,0) ---> 3^2 + 2 + 9^0 = 11
*/
template<typename T>
tCasilla3D convertToCasilla3D(const typename GrafoP<T>::vertice n, int N)
{
    int i,j,k;
    i = n/N;
    j = n%N;
    k=n/pow(N,2);
    return tCasilla3D(i,j,k);
}
/*
nodo 6 --> (2,0,0)
i=6/3=2
j=6%3=0
k=6/9=0
*/
bool adyacentes3d(tCasilla3D c1, tCasilla3D c2)
{
    return (abs(c1.i - c2.i) + abs(c1.j - c2.j)+abs(c1.k - c2.k) == 1);
}

//version 3D
template<typename tCoste>
typename GrafoP<tCoste>::nodo laberinto3(vector<tPared3D> paredes, tCasilla3D entrada, 
tCasilla3D salida, std::vector<typename GrafoP<tCoste>::vertice>& p)
{
    GrafoP<tCoste> g(pow(N,3)); //supergrafo

    //Recorrer todos los nodos
    (for int i=0; i<pow(N,3); i++) //vertice i
    {
        (for int j=0; j<pow(N,3); j++) //vertice j
        {
             {
                if(i==j) //poner a infinito el camino en el supergrafo
                    g[i][j]=GrafoP<tCoste>::INFINITO;  
                else
                {
                    if(adyacentes3d(convertToCasilla3D(i),convertToCasilla3D(j)))
                        g[i][j]=1;
                        g[j][i]=1;
                    else
                        g[i][j]==GrafoP<tCoste>::INFINITO;
                        g[j][i]==GrafoP<tCoste>::INFINITO;
                }
             }      
        }
    }

    //Poner las paredes del laberinto en la matriz de coste
    (for int i=0; i<paredes.size(); i++)
    {
        g[convertToNodo3D(paredes[i].c1, N)][convertToNodo3D(paredes[i].c2,N)] = GrafoP<tCoste>::INFINITO;
        g[convertToNodo3D(paredes[i].c2, N)][convertToNodo3D(paredes[i].c1,N)] = GrafoP<tCoste>::INFINITO;
    }

    //ya tenemos en g los costes aplicamos Dijkstra con el orgen en la casilla de salida
    GrafoP<T>::vertice nEntrada = convertToNodo(entrada,N);
    GrafoP<T>::vertice nSalida = convertToNodo(salida,N);
    vector<tCoste> coste = Dijkstra(g, nEntrada, p);

    return costes[nSalida];
}


#include "..\..\Implementaciones\matriz.hpp"
#include "..\..\Implementaciones\GrafoP.hpp"
#include "..\..\Implementaciones\Floyd.hpp"
#include "..\..\Implementaciones\Kruskal.hpp"
#include<math.h>
#include<vector>
/*
2. Se dispone de un laberinto de n×n casillas del que se conocen las casillas de entrada
y salida del mismo. Si te encuentras en una casilla sólo puedes moverte en las siguientes
cuatro direcciones (arriba, abajo, derecha, izquierda). Por otra parte, entre algunas de las
casillas hay una pared que impide moverse entre las dos casillas que separa dicha pared
(si no, no sería un verdadero laberinto).
Implementa un subprograma que dados
• un laberinto de N×N casillas, representado mediante una matriz de n×n,
• la lista de paredes del laberinto,
• la casilla de entrada, y
• la casilla de salida,
calcule el camino más corto para ir de la entrada a la salida y su longitud. 

Laberinto
E X _ _ _
_ _ _ _ X
_ X X S _
_ _ X _ _
_ _ _ _ _

Matriz de costes

entrada 0,0
salida 2,3

*/

//El grafo contiene nxn nodos, la matriz asociada sera de tamaño nxnxnxn
//costes 1 para cada arista.
//pasar de casilla a nodo y de nodo a casilla
// fila n/nodo
// columna n%nodo
//Cada pared es un par de casillas
//En lugar de pared una puerta que solo permite el paso en un solo sentido
//Piedra que impide pasar por un nodo concreto

//Otra opcion:3d

/*
template<typename tCoste>
struct tCoordenada
{
    typename GrafoP<tCoste>::vertice fila, columna;
    tCoordenada(typename GrafoP<tCoste>::vertice f, typename GrafoP<tCoste>::vertice c):fila(f), columna(c){}
};
template<typename tCoste>
struct tPared
{
    tCoordenada<tCoste> desde, hasta;
};

template<typename tCoste>
typename GrafoP<tCoste>::vertice convertirANodo(tCoordenada<tCoste> c, size_t tam)
{
    typename GrafoP<tCoste>::vertice nodo;
    nodo=tam*c.fila+c.columna;
    return nodo;
}
template<typename tCoste>
tCoordenada<tCoste> convertirACasilla(typename GrafoP<tCoste>::vertice nodo, size_t tam)
{
    return *new tCoordenada<tCoste>(tam/nodo, tam%nodo);
}
template<typename tCoste>
bool adyacente(tCoordenada<tCoste> c1, tCoordenada<tCoste> c2)
{
    return (abs(c1.fila-c2.fila)+abs(c1.columna-c2.columna)==1);
}
template<typename tCoste>
tCoste camino(matriz<tCoste>& laberinto, std::vector<tPared<tCoste>> paredes, 
tCoordenada<tCoste> entrada, tCoordenada<tCoste> salida)
{
    size_t longitud=0;
    GrafoP<tCoste> lab(pow(laberinto.dimension,4));
    //Hacemos que exista un camino entre cada par de nodos
    for(size_t i=0;i<lab.numVert();++i)
    {
        for(size_t j=0;j<lab.numVert();++j)
        {
            if(i==j)
                lab[i][j]=0;
            if(adyacente(convertirACasilla(i, lab.numVert()), convertirACasilla(j, lab.numVert())))
                lab[i][j]=1;
            else
                lab[i][j]=GrafoP<tCoste>::INFINITO;
        }
    }
    //Ponemos las paredes en el laberinto
    for(size_t i=0;i<paredes.size();++i)
    {
        lab[convertirANodo(paredes[i].desde, lab.numVert())][convertirANodo(paredes[i].hasta, lab.numVert())]=GrafoP<tCoste>::INFINITO;
        lab[convertirANodo(paredes[i].hasta, lab.numVert())][convertirANodo(paredes[i].desde, lab.numVert())]=GrafoP<tCoste>::INFINITO;
    }

    std::vector<typename GrafoP<tCoste>::vertice> P;
    std::vector<tCoste> costes=Dijkstra(lab, convertirANodo(entrada, lab.numVert()), P);

    return costes[convertirANodo(salida, lab.numVert())];
}

*/

//---LABERINTO ROSARIO---------------------
/*
Laberinto
Se dispone de un laberinto de n×n casillas del que se conocen las casillas de entrada
y salida del mismo. Si te encuentras en una casilla sólo puedes moverte en las siguientes
cuatro direcciones (arriba, abajo, derecha, izquierda). Por otra parte, entre algunas de las
casillas hay una pared que impide moverse entre las dos casillas que separa dicha pared
(si no, no sería un verdadero laberinto).
Implementa un subprograma que dados
• un laberinto de N×N casillas, representado mediante una matriz de n×n,
• la lista de paredes del laberinto,
• la casilla de entrada, y
• la casilla de salida,
calcule el camino más corto para ir de la entrada a la salida y su longitud.
*/
//grafo n^2, matriz de costes[n^2][n^2]
//crear conv de nodo a casilla y de casilla a nodo
//para las paredes
struct tPared
{
    tCasilla c1, c2;
    tPared(tCasilla c1_, tCasilla c2_):c1(c1_), c2(c2_){}
};

struct tPuerta
{
    tCasilla c1, c2;
};

struct tCasilla
{
    int i,j;
    tCasilla(int i, int j): i(i), j(j){}
};

struct nodo
{
    int n;
    nodo(int n_):n(n_){}
};

tCasilla convertToCasilla(const nodo n, int N)
{
    int i,j;
    i = n.n/N;   //n=5 N=3 ---> i=5/3 = 1
    j = n.n%N;   // j=5%3 --->  j=2
    return tCasilla(i,j);
}

nodo convertToNodo(const tCasilla c, int N)
{
	return nodo((c.i)*N+c.j); // (1,2)= 1*3+2=5=n
}

bool adyacentes(tCasilla c1, tCasilla c2)
{
    return (abs(c1.i - c2.i) + abs(c1.j - c2.j) == 1);
}

template<typename tCoste>
tCoste laberinto(matriz<bool> laberinto, std::vector<tPared> paredes, tCasilla entrada, tCasilla salida)
{
    int N=laberinto.dimension();
    GrafoP<tCoste> g(pow(N,2));
    matriz<typename GrafoP<tCoste>::vertice> p;

    //pasar los costes a la matriz g
    (for int i=0; i<g.numVert(); i++) //Recorremos todos los nodos del grafo
    {
        (for int j=0; j<g.numVert(); j++)
        {
            if(i==j)
            {
                g[i][j] = GrafoP<tCoste>::INFINITO;
            }
            if(adyacentes(convertToCasilla(i,N), convertToCasilla(j,N)))
            {
                g[i][j] = 1;
                g[j][i] = 1;
            }
            else
            {
                g[i][j] = GrafoP<tCoste>::INFINITO;
                g[j][i] = GrafoP<tCoste>::INFINITO;
            }
        }
    }
    
    //pasar las paredes del laberinto a la matriz de coste (cada pared es un par de casillas)
    (for int i=0; i<paredes.size(); i++)
    {
        //pared (0,1)-(0,2)= 
        g[convertToNodo(paredes[i].c1, N)][convertToNodo(paredes[i].c2,N)] = GrafoP<tCoste>::INFINITO;
        g[convertToNodo(paredes[i].c2, N)][convertToNodo(paredes[i].c1,N)] = GrafoP<tCoste>::INFINITO;
    }
    /*
    //pasar las paredes del laberinto a la matriz de coste (suponiendo que cada pared es una casilla)
    for(size_t i=0;i<paredes.size();++i)
    {
        size_t nodo=convertToCasilla(paredes[i]);
        for(size_t j=0;j<g.numVert();++i)
        {
            g[nodo][j]=GrafoP<tCoste>::INFINITO;
            g[j][nodo]=GrafoP<tCoste>::INFINITO;
        }
    }
    */

    //ya tenemos en g los costes ,aplicamos Dijkstra con el origen en la casilla de salida
    nodo nEntrada = convertToNodo(entrada,N);
    nodo nSalida = convertToNodo(salida,N);
    vector<tCoste> coste = Dijkstra(g, nEntrada, p);

    return coste[nSalida]; //Devuelve el coste desde nEntrada a nSalida
}

//version con puerta
template<typename tCoste>
void laberinto2(matriz<bool> laberinto, std::vector<tPuerta> puertas, tCasilla entrada, tCasilla salida)
{
    //como crearlo???
    int N=laberinto.dimension();
    GrafoP<tCoste> g(pow(N,2));
    matriz<typename GrafoP<tCoste>::vertice> p;

    //pasar los costes a la matriz g
    (for int i=0; i<pow(N,2); i++)
    {
        (for int j=0; j<pow(N,2); j++)
        {
            if(i==j)
            {
                g[i][j] = 0;
            }
            if(adyacentes(convertToCasilla(i,N), convertToCasilla(j,N)))
            {
                g[i][j] = 1;
                g[j][i] = 1;
            }
            else
            {
                g[i][j] = GrafoP<tCoste>::INFINITO;
                g[j][i] = GrafoP<tCoste>::INFINITO;
            }
        }
    }
    //pasar las paredes del laberinto a la matriz de coste
    (for int i=0; i<puertas.size(); i++)
    {
        g[convertToNodo(paredes[i].c1)][convertToNodo(paredes[i].c2,N)] = 1;
        g[convertToNodo(paredes[i].c2)][convertToNodo(paredes[i].c1,N)] = GrafoP<tCoste>::INFINITO;
    }

    //ya tenemos en g los costes aplicamos Dijkstra con el orgen en la casilla de salida
    nodo nEntrada = convertToNodo(entrada,N);
    nodo nSalida = convertToNodo(salida,N);
    vector<tCoste> coste = Dijkstra(g, entrada, p);
}

//version 3D
template<typename tCoste>
typename GrafoP<tCoste>::nodo laberinto3(vector<tPared> paredes, tCasilla entrada, 
tCasilla salida, matriz<typename GrafoP<tCoste>::vertice>& p)
{
    GrafoP<tCoste> g(pow(N,3)); //supergrafo
    typedef GrafoP<tCoste>::nodo nodo;

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
                    if(adyacentes3d(i,j))
                        g[i][j]=1;
                    else
                        g[i][j]==GrafoP<tCoste>::INFINITO;
                }
             }      
        }
    }

    //Poner las paredes del laberinto en la matriz de coste
    (for int i=0; i<paredes.size(); i++)
    {
        g[convertToNodo(paredes[i].c1)][convertToNodo(paredes[i].c2,N)] = GrafoP<tCoste>::INFINITO;
        g[convertToNodo(paredes[i].c2)][convertToNodo(paredes[i].c1,N)] = GrafoP<tCoste>::INFINITO;
    }

    //ya tenemos en g los costes aplicamos Dijkstra con el orgen en la casilla de salida
    nodo nEntrada = convertToNodo(entrada,N);
    nodo nSalida = convertToNodo(salida,N);
    vector<tCoste> coste = Dijkstra(g, nEntrada, p);

    return costes[nSalida];
}




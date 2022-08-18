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

#include<math.h>

typedef typename GrafoP<tCoste>::nodo nodo;

//para las paredes
struct tPared
{
    tCasilla c1, c2;
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
struct tCasilla3D
{
    int i,j,k;
    tCasilla3D(int i, int j, int k): i(i), j(j), k(k){}
};

struct nodo
{
    int n;
};

tCasilla convertToCasilla(const nodo n, int N)
{
    int i,j;
    i = n.n/N;
    j = n.n%N;
    return tCasilla(i,j);
}

tCasilla3D convertToCasilla3D(const nodo n, int N)
{
    int i,j,k;
    i = n.n/N;
    j = n.n%N;
    //Los nodos se agrupan en n grupos de n^2 nodos cada uno. Si tenemos un nodo, necesitamos
    //conocer en qué grupo está para saber el valor de k
    /*
    si la dimension del laberinto es 3 tenemos que hay 3 grupos de 9 nodos cada uno.
    El grupo 0 va desde el nodo 0 al 8
    El grupo 1 va desde el nodo 9 al 17
    El grupo 2 va desde el nodo 18 al 26
    Necesito una expresion que dado un nodo me devuelva en que grupo está
    */
    k=n.n/pow(N,2);
    return tCasilla3D(i,j,k);
}

nodo convertToNodo(const tCasilla c, int N)
{
	return nodo(c.i*N+c.j);
}

nodo convertToNodo3D(const tCasilla3D c, int N)
{
	return nodo(c.i*N+c.j);
}

bool adyacentes(tCasilla c1, tCasilla c2)
{
    return (abs(c1.i - c2.i) + abs(c1.j - c2.j) == 1);
}
bool adyacentes3d(tCasilla3D c1, tCasilla3D c2)
{
    return (abs(c1.i - c2.i) + abs(c1.j - c2.j)+abs(c1.k - c2.k) == 1);
}


template<typename tCoste>
camino laberinto(matriz[N][N] laberinto, vector<tPared> paredes, tCasilla entrada, tCasilla salida, int N)
{
    //como crearlo???
    GrafoP<tCoste> g(pow(N,2));
    matriz<typename GrafoP<tCoste>::vertice> p;

    //pasar los costes a la matriz g
    (for int i=0; i<pow(N,2); i++)
    {
        (for int j=0; j<pow(N,2); j++)
        {
            if(i==j)
            {
                g[i][j] = GrafoP<tCoste>::INFINITO;;
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
    (for int i=0; i<paredes.size(); i++)
    {
        g[convertToNodo(paredes[i].c1, N)][convertToNodo(paredes[i].c2,N)] = GrafoP<tCoste>::INFINITO;
        g[convertToNodo(paredes[i].c2,N)][convertToNodo(paredes[i].c1,N)] = GrafoP<tCoste>::INFINITO;
    }

    //ya tenemos en g los costes aplicamos Dijkstra con el orgen en la casilla de salida
    nodo nEntrada = convertToNodo(entrada,N);
    nodo nSalida = convertToNodo(salida,N);
    vector<tCoste> coste = Dijkstra(g, nEntrada, p);

    return coste[nSalida];
    return p;

}

//version con puerta
template<typename tCoste>
camino laberinto2(matriz[N][N] laberinto, vector<tPuerta> puertas, tCasilla entrada, tCasilla salida, int N)
{
    //como crearlo???
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
camino laberinto3(matriz[N][N][N] laberinto, vector<tPared> paredes, tCasilla entrada, tCasilla salida, int N)
{
    //como crearlo???
    GrafoP<tCoste> g(pow(N,3));
    matriz<typename GrafoP<tCoste>::vertice> p;

    //pasar los costes a la matriz g
    (for int i=0; i<pow(N,3); i++)
    {
        (for int j=0; j<pow(N,3); j++)
        {
            //si está en la diagonal
            if(i == j)
            {
                g[i][j] = 0;
            }

            si dos casillas son adyacentes
            if(adyacentes3d(convertToCasilla(i,N), convertToCasilla(j,N)))
            {
                //revisar
                g[i][j] = 1;
                g[j][i] = 1;

            }
            else
            {
                //revisar
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

Casilla2D: N = 3
TABLERO
0	1	2
3	4	5
6	7	8
Casilla 0: (0,0) nodo = 0*3+0 = 0
Casilla 1: (0,1) nodo = 0*3+1 = 1

Casilla3D: N = 3
Casilla 0: (0,0,0) nodo: c.i*N+c.j = 0*3+0 = 0
Casilla 1: (0,1,0) nodo =



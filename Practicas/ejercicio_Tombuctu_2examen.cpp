#include "Particion.hpp"
#include <math.h>
#include<vector>
#include "..\Implementaciones\GrafoP.hpp"
#include "..\Implementaciones\Grafo.hpp"
#include "..\Implementaciones\matriz.hpp"
/*
El archipiélago de Tombuctú2 está formado por un número desconocido de islas,
cada una de las cuales tiene, a su vez, un número desconocido de ciudades, las cuales
tienen en común que todas y cada una de ellas dispone de un aeropuerto. 

****Sí que se
conoce el número total de ciudades del archipiélago (podemos llamarlo N, por ejemplo).****


Dentro de cada una de las islas existen carreteras que permiten viajar entre todas
las ciudades de la isla. No existen puentes que unan las islas y se ha decidido que la
opción de comunicación más económica de implantar será el avión.


Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las
ciudades del archipiélago. Se dispone de un grafo (matriz de adyacencia) en el que se
indica si existe carretera directa entre cualesquiera dos ciudades del archipiélago. 

El objetivo de nuestro problema es encontrar qué líneas aéreas debemos implantar para
poder viajar entre todas las ciudades del archipiélago, siguiendo los siguientes criterios:
1) Se implantará las lineas necesarias para viajar a todas las ciudades
2) La línea aérea escogida entre cada par de islas será la que haga mas corto viajar por todas las ciudades (Kruskall)

Así pues, dados los siguientes datos:
· Lista de ciudades de Tombuctú2 representada cada una de ellas por sus
coordenadas cartesianas.

. Lista de ciudades ordenadas por islas(*)--->Vector de pertenencia

· Matriz de adyacencia de Tombuctú que indica las carreteras existentes en
dicho archipiélago.

Implementen un subprograma que calcule y devuelva las líneas aéreas necesarias para
comunicar adecuadamente el archipiélago siguiendo los criterios anteriormente
expuestos.
*/

//ESTE ES EL DEL EXAMEN, LA DIFERENCIA ES QUE EN ESTE SE SUPONE QUE TE DAN UNA LISTA CON TODAS LAS CIUDADES ORDENADAS POR ISLAS
// ES DECIR LAS PRIMERAS n SON DE LA ISLA 1 LAS SIGUIENTES m SON LA ISLA 2 HASTA TERMINAR LAS ISLAS.
//En este no hay que utilizar el TAD partición, que por eso suspendimos todos por utilizarlo.

//Como te dice que tienes una lista con las ciudades ordenadas por islas y como tenemos la matriz de adyacencia podemos sacar el 
//numero de ciudades que tiene cada isla y el numero de islas utilizando la matriz de adyacencia. 

//OTRA DIFERENCIA ES QUE NO TE PIDE LA LINEA/PUENTE MAS CORTO SINO EL QUE HAGA MENOS COSTOSO EL VIAJAR ENTRE CUALQUIERA CIUDAD,
//LO QUE QUIERE DECIR QUE SE APLIQUE floyd() Y SE SUME Y NOS TENDREMOS QUE QUEDAR CON LA LINEA/PUENTE QUE MINIMICE ESA SUMA
struct Coordenada
{
    double x,y;
    Coordenada(double x_=0.0, double y_=0.0):x(x_), y(y_){}
};

template <typename tCoste>
tCoste distancia(Coordenada a, Coordenada b)
{
    return sqrt(pow(abs(a.x-b.x), 2) + pow(abs(a.y-b.y), 2));
}

//para guardar cada linea encontrada
template<typename tCoste>
struct linea
{
	int origen, destino;
	tCoste coste;
	linea(int o, int d, tCoste c): origen(o), destino(d), coste(c) {}
};

template<typename tCoste>
linea<tCoste> tombuctu(const Grafo& matAdy, int n, const std::vector<Coordenada>& ciudades, 
std::vector<size_t> ciudades_ordenadas)
{
	GrafoP<tcoste> g(n); //grafo ponderado, los inicializa a infinito
    //Unir por avion todas las ciudades, excepto aquellos pares de ciudades que pertenezcan a la misma isla
	for(int i=0; i<=n; i++)
	{
		for(int j=0; j<=n; j++)
		{
            if(ciudades_ordenadas[i]!=ciudades_ordenadas[j]) //ciudades con distinto representante
            //en el vector de pertenencia , pertenecen a islas diferentes
			    g[i][j] = distancia(ciudades[i], ciudades[j]);
		}
	}
	//tengo en g todas los costes
    //Se usa Kruskall porque nos piden usar el numero necesario de lineas aereas, no estamos limitados
    //a una linea entre cada par de islas
	GrafoP<tCoste> gCoste= Kruskal(g);

    for(int i=0; i<=n; i++)
	{
		for(int j=0; j<=n; j++)
        {
            if(gCoste[i][j]!=GrafoP<tCoste>::INFINITO)
            {
                if(matAdy[i][j]==false)
                {
                    std::cout << "Linea aerea entre la ciudad " << i << " y la ciudad " << j << std::endl;
                }
            }
        }
    }
}
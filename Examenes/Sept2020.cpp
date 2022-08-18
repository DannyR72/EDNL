/*
El archipiélago de Tombuctú2 está formado por un número desconocido de islas,
cada una de las cuales tiene, a su vez, un número desconocido de ciudades, las cuales
tienen en común que todas y cada una de ellas dispone de un aeropuerto. Sí que se
conoce el número total de ciudades del archipiélago (podemos llamarlo N, por ejemplo).

Dentro de cada una de las islas existen carreteras que permiten viajar entre todas
las ciudades de la isla. No existen puentes que unan las islas y se ha decidido que la
opción de comunicación más económica de implantar será el avión.

Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las
ciudades del archipiélago. 

Se dispone de un grafo (matriz de adyacencia) en el que se
indica si existe carretera directa entre cualesquiera dos ciudades del archipiélago. 

El objetivo de nuestro problema es encontrar qué líneas aéreas debemos implantar para
poder viajar entre todas las ciudades del archipiélago, siguiendo los siguientes criterios:

1) Se implantará las lineas aereas necesarias para viajar a todas las ciudades
2) La línea aérea escogida entre cada par de islas será la que haga mas corto viajar por todas las ciudades

Así pues, dados los siguientes datos:

· Lista de ciudades de Tombuctú2 representada cada una de ellas por sus
coordenadas cartesianas.
. Lista de ciudades ordenadas por islas - 0 1 3 4 5 2
· Matriz de adyacencia de Tombuctú que indica las carreteras existentes en
dicho archipiélago,

  0 1 2 3 4 5 
0 F T F F T F
1 T F F T F T
2
3
4
5
Particion p(6)
if(p.encontrar(0)!=p.encontrar(1))
    p.unir(0,1);
    
p.unir(0,4);








Implementen un subprograma que calcule y devuelva las líneas aéreas necesarias para
comunicar adecuadamente el archipiélago siguiendo los criterios anteriormente
expuestos.
*/

//ESTE ES EL DEL EXAMEN, LA DIFERENCIA ES QUE EN ESTE SE SUPONE QUE TE DAN UNA LISTA CON TODAS LAS CIUDADES ORDENADAS 
//POR ISLAS
// ES DECIR LAS PRIMERAS n SON DE LA ISLA 1 LAS SIGUIENTES m SON LA ISLA 2 HASTA TERMINAR LAS ISLAS.
//En este no hay que utilizar el TAD partición, que por eso suspendimos todos por utilizarlo.
//Como te dice que tienes una lista con las ciudades ordenadas por islas y como tenemos la matriz de adyacencia 
//podemos sacar el 
//numero de ciudades que tiene cada isla y el numero de islas utilizando la matriz de adyacencia. 
//OTRA DIFERENCIA ES QUE NO TE PIDE LA LINEA/PUENTE MAS CORTO SINO EL QUE HAGA MENOS COSTOSO EL VIAJAR ENTRE
// CUALQIERA CIUDAD,
//LO QUE QUIERE DECIR QUE SE APLIQUE floyd() Y SE SUME Y NOS TENDREMOS QUE QUEDAR CON LA LINEA/PUENTE QUE MINIMICE
// ESA SUMA
#include<vector>
#include "..\Implementaciones\Grafo.hpp"
#include "..\Implementaciones\GrafoP.hpp"

struct Coordenada
{
    double x,y;
    Coordenada(double x_=0.0, double y_=0.0):x(x_), y(y_){}
};

template <typename tCoste>
tCoste Distancia(Coordenada a, Coordenada b)
{
    return sqrt(pow(abs(a.x-b.x), 2), pow(abs(a.y-b.y), 2));
}

//para guardar cada linea encontrada
template<typename tCoste>
struct linea
{
	int origen, destino;
	tCoste coste;
	linea(int o, int d, tCoste c): origen(o), destino(d), coste(c) {}
};

bool Existe(int representante, std::vector<typename Grafo::vertice> representantes)
{
    bool encontrado = false;
    int i = 0;

    while (!encontrado && i < representantes.size())
    {
        encontrado = representantes[i] == representante;
        i++;
    }

    return encontrado;
}

template<typename tCoste>
std::vector<linea<tCoste>> Lineas_Aereas(const std::vector<Coordenada>& Ciudades, const Grafo& Tombuctu)
{
    GrafoP<tCoste> G(N_ciudades); //grafo ponderado

    // Recorro el grado Tombuctu
    for (int i = 0; i < Ciudades.size(); i++)
    {
        for (int j = 0; j < Ciudades.size(); j++)
        {
            if (Tombuctu[i][j]) // Si las ciudades están comunicadas, se encuentran en la misma isla
            {
                G[i][j] = Distancia(Ciudades[i], Ciudades[j]); // Añadir distancia entre ciudades al grafo 
            }
            else
            {
                G[i][j] = GrafoP<tCoste>::INFINITO;
            }
    	}
    }

    //sacamos el numero de islas que hay
    int i = 0;
    int n_islas = 0;
    while(i<Ciudades.size())
    {
    	for(int j = i; j<Ciudades.size(); j++)
    	{
    		//si no es verdadero,no hay carretera
    		if(!G[i][j])
    			n_islas++;
    		i=j;
    	}
    }

    //P dividido en subconjunto igual al numero de islas
    //G tengo todas las distancias de las ciudades que están comunicadas
    //N_islas tengo el numero de islas

    //tengo que almacenar los representantes
    vector<typename Grafo::vertice> representantes(N_islas);
    while (n_representantes <= N_islas && i <= N_islas)  // Rellenar el vector representantes
    {
        if (!Existe(P.encontrar(i), representantes))
        {
            representantes.push_back(P.encontrar(i));
            n_representantes++;
        }
     	i++;
    }


    //tengo los representantes en el vector representantes
    //vamos a calcular las lineas
    tCoste costeLinea = GrafoP<tCoste>::INFINITO;
    vector<linea> lineas(N_islas);

    for(int i=0; i<repesentantes.size(); i++)
    {
    	for(int j=0; j<=N_ciudades; i++)
    	{
    		//si el representante no es el mismo significa que están en subconjuntos diferentes
    		//y por lo tanto son ciudades de islas distintas
    		if(p.encontrar(j)!=representantes[i])
    		{
    			//calculo la distancia de la ciudad i a la j (posible linea aerea)
    			tCoste coste = Distancia(Ciudades[i], Ciudades[j]);
    			//si el coste es menor me quedo con él
    			if(coste < costeLinea)
    				costeLinea=coste;
    				int origen = i;
    				int destino = j;
    		}
    	}
    	//guardo el costeLinea y las ciudades que unen
    	lineas.push_back(linea(i,j, costeLinea));
    }

    return lineas;
}  
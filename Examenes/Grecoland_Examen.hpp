/*
El archipiélago de Grecoland (Nozuelandia) está formado únicamente por tres islas, Fobos, Deimos 
y Europa que tienen N1, N2 y N3 ciudades, respectivamente, todas ellas costeras.

Se dispone de la relación de ciudades de cada una de las tres islas, representadas por sus coordenadas cartesianas.

Dentro del programa COMUNICA de la ONU hemos conseguido fondos para comunicar todas las ciudades de Grecoland. 

Las condiciones del programa COMUNICA indican que se sufragarán todos los costes de construcción 
de las comunicaciones (carreteras y puentes) al menor coste posible.

Se sabe que la construcción de cualquier puente es más cara que la de cualquier carretera. 

También es conocido que el coste de construcción de una carretera o de un puente es proporcional a su longitud.
En estas condiciones se debe calcular (mediante una función) qué carreteras y puentes deben 
construirse para comunicar entre sí todas las ciudades de Grecoland, dados los siguientes datos:

1.	Relación de ciudades de Fobos, representadas mediante sus coordenadas cartesianas.
2.	Relación de ciudades de Deimos, representadas mediante sus coordenadas cartesianas.
3.	Relación de ciudades de Europa, representadas mediante sus coordenadas cartesianas.



PLANTEAMIENTO

Colocar carreteras entre todas las ciudades de cada isla (ditancia*precio_carretera)

Colocar puentes entre todas las ciudades que pertenecen a islas diferentes (distancia*precio_puente)

Una vez que todas las ciudades estan conectadas aplicar Kruskal para obtener un solo camino minimo que una 
todas las ciudades.

*/

#include<vector>
#include<cmath>
#include "GrafoP.hpp"
#include "particion.hpp"
typedef int tCoste;
 using namespace std;

 struct ciudad
 {
 	double x, y;
 	ciudad(double x=0.0, double y=0.0): x(x), y(y) {}
     bool operator==(const ciudad& c){return (x==c.x && y==c.y);}
 };

struct Puente
{
	tCoste dPuente;
	ciudad ciudad1, ciudad2;
	Puente(tCoste d, ciudad c1, ciudad c2): dPuente(d), ciudad1(c1), ciudad2(c2) {}
};


double distancia(const ciudad& a, const ciudad& b)
{
 	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

bool pertenece(std::vector<ciudad> v, ciudad c)
{
    bool r=false;
    for(size_t i=0;i<v.size() && !r;++i)
    {
        if(v[i]==c)
            r=true;
    }
    return r;
}

bool misma_isla(vector<ciudad> Fobos, vector<ciudad> Deimos, vector<ciudad> Europa, ciudad i, ciudad j)
{

    if(pertenece(Fobos, i) && pertenece(Fobos, j))
        return true;
    else
    {
        if(pertenece(Deimos, i) && pertenece(Deimos, j))
            return true;
        else
        {
            if(pertenece(Europa, i) && pertenece(Europa, j))
                return true;
            else
                return false;   
        }
    }
}

template <typename tCoste>
GrafoP<tCoste> grecoland(vector<ciudad> Fobos, vector<ciudad> Deimos, vector<ciudad> Europa, double CosteCar, double CostePu,
    double CosteCarIni, double CostePuIini)
{
	int nT = Fobos.size()+Deimos.size()+Europa.size(); //Tamaño del supergrafo
	//creamos el super grafo para las tres islas
	GrafoP<tCoste> superGrafo(nT), arbolRec(nT);
    
	//añadimos las distancias correspodientes al super grafo
	for(int i=0; i<nT; i++)
	{
		for(int j=0; j<nT; j++)
		{
            if(misma_isla(Fobos, Deimos, Europa, i,j))
                 superGrafo[i][j] = superGrafo[j][i]=CosteCarIni +  CosteCar * distancia(ciudades[i], ciudades[j]);
            else
                superGrafo[i][j] = superGrafo[j][i]=  CostePuIini + CostePu * distancia(ciudades[i], ciudades[j]);
		}
	}
	arbolRec = Kruskal(superGrafo);	
    return arbolRec;
}

/*
Isla1
10 5
20 10

Isla2
1 6
3 2

   0  1 2 3
0  10 5   8
1  20 10
2  4    1 6
3       3 2
4           8 9
5       0   1 3





*/
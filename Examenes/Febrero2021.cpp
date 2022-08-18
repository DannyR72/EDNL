/*
EXAMEN GRAFO FEBRERO 2021
El archipiélago de Grecoland (Nozuelandia) está formado únicamente por tres islas, Fobos, Deimos y Europa 
que tienen N1, N2 y N3  ciudades, respectivamente, todas ellas costeras.

Se dispone de la relación de ciudades de cada una de las tres islas, representadas por sus coordenadas cartesianas.

Dentro del programa COMUNICA de la ONU hemos conseguido fondos para comunicar todas las ciudades de Grecoland. 
Las condiciones del programa COMUNICA indican que se sufragarán todos los costes de construcción de las comunicaciones
(carreteras y puentes) al menor coste posible.

Se sabe que la mera construcción de un puente o una carretera ya implica una serie de costes fijos,
que difieren para el caso de carretera y puente. Además, el coste por unidad de longitud para carreteras y 
puentes también es distinto.

En estas condiciones se debe calcular (mediante una función) qué carreteras y puentes deben construirse para 
comunicar entre sí todas las ciudades de Grecoland, dados los siguientes datos:

Relación de ciudades de Fobos, representadas mediante sus coordenadas cartesianas.
Relación de ciudades de Deimos, representadas mediante sus coordenadas cartesianas.
Relación de ciudades de Europa, representadas mediante sus coordenadas cartesianas.

Coste inicial de construcción de un puente.
Coste inicial de construcción de una carretera.
Coste adicional por unidad de longitud de construcción de un puente.
Coste adicional por unidad de longitud de construcción de una carretera.

EXAMEN ÁRBOLES 2021
Implementa una función genérica que transforme un árbol binario de un tipo genérico T, 
eliminando los descendientes propios de todos aquellos nodos cuyo contenido sea, al mismo tiempo, 
mayor o igual que el de sus ascendientes propios y menor o igual que el de sus descendientes propios.

*/
#include "..\Implementaciones\GrafoP.hpp"

template <typename tCoste>
GrafoP<tCoste> grecoland(vector<ciudad> Fobos, vector<ciudad> Deimos, vector<ciudad> Europa, 
double CosteCar, double CostePu, double CosteICar, double CosteIPu)
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
                 superGrafo[i][j] = superGrafo[j][i]= CosteICar+ (CosteCar * distancia(ciudades[i], ciudades[j]));
            else
                superGrafo[i][j] = superGrafo[j][i]= CosteIPu +  (CostePu * distancia(ciudades[i], ciudades[j]));
		}
	}
	arbolRec = Kruskal(superGrafo);	
    return arbolRec;
}
/*
El archipiélago de Grecoland (Nozuelandia) está formado únicamente por tres islas:
Fobos, Deimos y Europa que tienen N1, N2 y N3 ciudades, respectivamente, todas ellas costeras.

Se dispone de la relación de ciudades de cada una de las tres islas, representadas por sus coordenadas cartesianas.

Dentro del programa COMUNICA de la ONU hemos conseguido fondos para comunicar todas las ciudades de Grecoland. 
Las condiciones del programa COMUNICA indican que se sufragarán todos los costes de construcción 
de las comunicaciones (carreteras y puentes) al MENOR coste posible.

Se sabe que la construcción de cualquier puente es más cara que la de cualquier carretera. 
También es conocido que el coste de construcción de una carretera o de un puente es proporcional a su longitud.
En estas condiciones se debe calcular (mediante una función) qué carreteras y puentes deben 
construirse para comunicar entre sí todas las ciudades de Grecoland, dados los siguientes datos:

1.	Relación de ciudades de Fobos, representadas mediante sus coordenadas cartesianas.
2.	Relación de ciudades de Deimos, representadas mediante sus coordenadas cartesianas.
3.	Relación de ciudades de Europa, representadas mediante sus coordenadas cartesianas.
*/
/*


    FOBOS          DEIMOS        EUROPA

    0  1           0 1 2          0 1 2 3




            0     1       2    3    

            4   5     6    7 

               8   
















*/

#include<math.h>
#include<vector>
#include "..\Implementaciones\GrafoP.hpp"
 using namespace std;

 struct ciudad
 {
 	double x, y;
 	ciudad(double x=0.0, double y=0.0): x(x), y(y) {}
     bool operator==(const ciudad& c){return (x==c.x && y==c.y);}
 };

template<typename tCoste>
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

bool pertenece(std::vector<ciudad> v, ciudad c) //Devuelve si una ciudad pertenece a un vector de ciudades
{
    bool r=false;
    for(size_t i=0;i<v.size() && !r;++i)
    {
        if(v[i]==c)
            r=true;
    }
    return r;
}

//Devuelve si dos ciudades pertenecen a la misma isla
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
void grecoland(vector<ciudad> Fobos, vector<ciudad> Deimos, vector<ciudad> Europa, tCoste CosteCarr,
 tCoste CostePu)
{
	int nT = Fobos.size()+Deimos.size()+Europa.size();
	//creamos el super grafo para almacenar las distancias entre las ciudades de las tres islas
	GrafoP<tCoste> SG, arbolRec;
    SG=superGrafo(nT);

    //Creamos un vector con todas las ciudades
    std::vector<ciudad> ciudades(nT);
    //Recorremos los tres vectores de ciudades y rellenamos el vector ciudades con ellas
    ciudades=crearVector(Fobos, Deimos, Europa);
    
	//añadimos las distancias correspodientes al super grafo
	for(int i=0; i<nT; i++)
	{
		for(int j=0; j<nT; j++)
		{
            if(misma_isla(Fobos, Deimos, Europa, i,j))
                SG[i][j] = CosteCarr * distancia(ciudades[i], ciudades[j])
            else
                SG[i][j] = CostePu * distancia(ciudades[i], ciudades[j])
		}
	}
	return arbolRec = Kruskal(SG);	
}
/*
Fobos 2 ciudades (0,1)
Deimos 3 ciudades (2,3,4)
Europa 2 ciudades (5,6)
Supergrafo 7x7

  0 1 2 3 4 5 6 
0 F F
1 F F
2     D D D
3     D D D
4     D D D
5           E E
6           E E

*/
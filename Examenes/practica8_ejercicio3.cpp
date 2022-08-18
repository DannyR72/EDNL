/*
3. Eres el orgulloso dueño de una empresa de distribución. Tu misión radica en
distribuir todo tu stock entre las diferentes ciudades en las que tu empresa dispone de
almacén.
Tienes un grafo representado mediante la matriz de costes, en el que aparece el coste
(por unidad de producto) de transportar los productos entre las diferentes ciudades del
grafo.
Pero además resulta que los Ayuntamientos de las diferentes ciudades en las que
tienes almacén están muy interesados en que almacenes tus productos en ellas, por lo
que están dispuestos a subvencionarte con un porcentaje de los gastos mínimos de
transporte hasta la ciudad.
He aquí tu problema. Dispones de
• el centro de producción, nodo origen en el que tienes tu producto (no tiene
almacén),
• una cantidad de unidades de producto (cantidad),
• la matriz de costes del grafo de distribución con n ciudades (almacenes),
• la capacidad de almacenamiento de cada una de ellas,
• el porcentaje de subvención (sobre los gastos mínimos) que te ofrece cada
Ayuntamiento.
Las diferentes ciudades (almacenes) pueden tener distinta capacidad, y además la
capacidad total puede ser superior a la cantidad disponible de producto, por lo que
debes decidir cuántas unidades de producto almacenas en cada una de las ciudades.
Debes tener en cuenta además las subvenciones que recibirás de los diferentes
Ayuntamientos, las cuales pueden ser distintas en cada uno y estarán entre el 0% y el
100% de los costes mínimos.
La solución del problema debe incluir las cantidades a almacenar en cada ciudad bajo
estas condiciones y el coste mínimo total de la operación de distribución para tu
empresa.
*/
#include "..\Implementaciones\GrafoP.hpp"
#include "..\Implementaciones\Floyd.hpp"

template<typename tCoste>
tCoste ejercicio3(const GrafoP<tCoste>& G, typename GrafoP<tCoste>::vertice centro, size_t cantidad,
std::vector<size_t> capacidades, std::vector<size_t> porcentajes, std::vector<size_t>& cantidades)
{
    //Devolvemos el coste minimo total de la operacion de distribucion (la suma de todos los caminos que va tomando)
    //Devolvemos por parametro de salida un vector con las cantidades que se han almacenado en cada ciudad
    capacidades[centro]=0; //el centro de produccion no tiene almacen
    tCoste menorCoste, costeTotal=0;
    //Variables para usar Floyd 
    matriz<tCoste> costes;
    matriz<typename GrafoP<tCoste>::vertice> caminos;

    costes=Floyd(G, caminos);

    //Vector para marcar aquellas ciudades que ya han sido visitadas
    std::vector<bool> visitadas(G.numVert(), false);
    GrafoP<tCoste>::vertice ciudadActual=centro, mejorCiudad;
    visitadas[centro]=true;

    while(cantidad>0)
    {
        //Calculamos cual es la mejor ciudad donde almacenar stock 
        //(aquella que su coste sea el menor posible incluyendo la subvencion)
        menorCoste=GrafoP<tCoste>::INFINITO;
        for(size_t i=0;i<G.numVert();++i)
        {
            if((costes[ciudadActual][i]-(costes[ciudadActual][i]*porcentajes[i]/100))<menorCoste)
            {
                menorCoste=costes[ciudadActual][i]-(costes[ciudadActual][i]*porcentajes[i]/100);
                ciudadActual=i;
            }
        }
        if(cantidad>capacidades[i])
        {
            cantidad=cantidad-capacidades[i];
            cantidades[i]=capacidades[i];
        }
        else
        {
            cantidades[i]=cantidad;
            cantidad=0;
        }
        visitadas[i]=true;
        costeTotal+=menorCoste;
    }
    return costeTotal;
}

























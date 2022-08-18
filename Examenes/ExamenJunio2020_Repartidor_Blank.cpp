#include "..\Implementaciones\GrafoP.hpp"
#include "..\Implementaciones\matriz.hpp"
#include "..\Implementaciones\Floyd.hpp"
typedef int tCoste;
typedef GrafoP<tCoste>::vertice nodo;

//Prototipos de funciones auxiliares

//Funcion que Calcula el proximo cliente a atender en funcion de la distancia
//Funcion que Comprueba si todos los clientes han sido atendidos

int pedido();

tCoste calcularDistancia(const GrafoP<tCoste>& g, int capacidad, nodo& almacen)
{
    //0.Declaracion e inicializacion de variables y estructuras necesarias para el problema
    tCoste distanciaTotal=0;
    std::vector<bool> clientesAtendidos(g.numVert());
    clientesAtendidos[almacen]=true;
    matriz<tCoste> costesMinimos;
    matriz<nodo> caminos;
    nodo nodoActual=almacen;
    int carga=capacidad;

    //1.-Necesitamos calcular las distancias minimas entre todos los nodos del grafo (Floyd)
    costesMinimos=Floyd(g, caminos);

    //2.-Mientras quede al menos un cliente sin atender continua el reparto
    while(TodosAtendidos(clientesAtendidos))
    {
        //Si el pedido del cliente es menor que la carga del camion
        
            //Se descarga del camion el pedido
            
            //Se entrega el pedido al cliente actual (se marca el cliente como atendido)
            
        
        //Si no
    
            //Se vacía toda la mercancia del camion
            
            //Hay que ir al almacen y reponer toda la mercancia hasta llenar la capacidad del camion
            
    }    
    //Devolver la distancia total que ha recorrido el camion
    return distanciaTotal;
}
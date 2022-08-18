#include "..\Implementaciones\GrafoP.hpp"
#include<vector>
#include "Floyd.hpp"
#include "matriz.hpp"
typedef double tCoste;
typedef GrafoP<tCoste>::vertice nodo;

//Prototipos
nodo proximoCliente(const std::vector<tCoste>&, const std::vector<bool>&); //Calcula el proximo cliente en funcion de la distancia
bool repartoTerminado(const std::vector<bool>&); //Comprueba si todos los clientes han sido atendidos
tCoste calcularDistancia(const GrafoP<tCoste>&, int, nodo&); //Algoritmo principal
int pedido();

tCoste calcularDistancia(const GrafoP<tCoste>& g, int capacidad, nodo& almacen)
{
    //0.Declaracion e inicializacion de variables
    tCoste distanciaTotal=0;
    int cantidadRestante;
    nodo clienteActual, clienteProximo;
    std::vector<bool> clientesAtendidos(g.numVert(), false);
    clientesAtendidos[almacen]=true;
    clienteActual=almacen;
    cantidadRestante=capacidad;

    //1.-Necesitamos calcular las distancias minimas entre todos los nodos del grafo
    matriz<tCoste> distanciasMinimas;
    matriz<nodo> caminos;
    distanciasMinimas=Floyd(g,caminos);

    //2.-Mientras quede al menos un cliente sin atender continua el reparto
    while(!repartoTerminado(clientesAtendidos))
    {
        clienteProximo=proximoCliente(distanciasMinimas[clienteActual], clientesAtendidos);
        distanciaTotal+=distanciasMinimas[clienteActual][clienteProximo];
        clienteActual=clienteProximo;

        if(pedido()<cantidadRestante)
        {
            //Se descarga del camion el pedido
            cantidadRestante-=pedido();
            //Se entrega el pedido al cliente actual
            clientesAtendidos[clienteActual]=true;
        }
        else
        {
            //Se vacía toda la mercancia del camion
            cantidadRestante=0;
            
            //Hay que ir al almacen
            distanciaTotal+=distanciasMinimas[clienteActual][almacen];
            clienteActual=almacen;
            cantidadRestante=capacidad;
        }
    }
    return distanciaTotal;
}
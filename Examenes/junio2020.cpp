#include<vector>
template<typename tCoste>
tCoste calcular_distancia(GrafoP<tCoste>& g, int capacidad, GrafoP<tCoste>::vertice almacen) 
{
    //Inicializar variables
    tCoste distancia_total=0;
    std::vector<tCoste> costes;
    std::vector<GrafoP<tCoste>::vertice> caminos;
    GrafoP<tCoste>::vertice proximo_cliente;
    std::vector<bool> clientes_servidos(g.numVert(),false);
    clientes_servidos[almacen]=true;
    capacidad_actual=capacidad;


    while(!todos_servidos(clientes_servidos))
    {
    costes=Dijkstra(g, almacen, caminos);
    proximo_cliente=proximo(costes);

    distancia_total=distancia_total+costes[proximo_cliente];

    if(Pedido()<=capacidad)
    {
        capacidad_actual=capacidad_actual-Pedido();
        clientes_servidos[proximo_cliente]=true;
    }
    else
    {
        //Voy al almacen
        costes=Dijkstra(g, proximo_cliente, caminos);
        distancia_total=distancia_total+costes[almacen];
        proximo_cliente=almacen;
        //Cargo el camion
        capacidad_actual=capacidad;
    }

    return distancia_total;
}
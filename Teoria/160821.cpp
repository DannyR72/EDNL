#include "..\Implementaciones\Grafo.hpp"
#include "..\Implementaciones\GrafoP.hpp"



void f()
{
    Grafo g(5); //El constructor inicializa la matriz de adyacencia a false, esto indica que todos
    //los nodos estan desconectados entre si

    //Empezamos a realizar conexiones directas
    g[2][4]=true;
    g[4][2]=true;

    //En los examenes se suelen usar costes numericos para indicar los pesos de las aristas
    GrafoP<int> GP(5);////El constructor inicializa la matriz de costes a INFINITO, esto indica que todos
    //los nodos estan desconectados entre si

    GP[0][1]=10; //Conectamos el nodo 0 con el 1 con coste 10
}

template<typename T>
int comprobar(const GrafoP<T>& G)
{
    if(G[0][4]==GrafoP<T>::INFINITO)
        return 0;
    else
        return 1;
}

//lista de adyacencia
/*
0    1, 2
1    0, 3, 4
2    4
3    1, 2
4    2, 3
*/
//lista de costes

/*
0    1:10, 2:30  //Cada elemento de la lista esta formado por --> nodo conectado : coste del nodo conectado
1    0:15, 3:10, 4:100
2    4
3    1, 2
4    2, 3
*/

//Funcion para leer los caminos del vector de caminos de Dijkstra
void mostrarCamino(const std::vector<typename Grafo::vertice>& caminos, typename Grafo::vertice origen)
{
    size_t j;
    bool primero=false;
    for(size_t i=0;i<caminos.size();++i)
    {
        j=i;
        while(caminos[j]!=origen)
        {
            if(!primero)
            {
                std::cout << j << "<-";
                primero=true;
            } 
            std::cout << caminos[j] << "<-";
            j=caminos[j];
        }  
        std::cout << origen << std::endl; 
        primero=false;
    }
}

//Matriz de adyacencia=Grafo no ponderado

/*
F T F T T
F F T F F
F F F F T
F F T F T
F F F F F 
*/
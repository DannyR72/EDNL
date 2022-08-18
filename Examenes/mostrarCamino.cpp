#include "..\Implementaciones\Grafo.hpp"
#include<vector>
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

int main()
{
    std::vector<typename Grafo::vertice> caminos(5);
    caminos[0]=0;
    caminos[1]=0;
    caminos[2]=3;
    caminos[3]=0;
    caminos[4]=2;

    mostrarCamino(caminos, 0);
}
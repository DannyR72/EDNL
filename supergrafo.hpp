/*
tren
(0) --------- (1) -------- (2)
      5             50

Matriz de costes tren
_  5  _
5  _  50
_  50  _

avion
(0) --------- (1) -------- (2)
       40            10

Matriz de costes avion
_  40  _
40  _  10
_  10  _


tren                avion
(0)                  (3)
 |                    |
 | 5                  | 40
 |         20         |
(1)------------------(4)
 |                    |
 | 50                 | 10
 |                    |
(2)                  (5)

0  1  2  3  4  5
_  5  _  _  _  _
5  _ 50  _  20  _
_  50 _  _  _  _
_ _  _  _  40 _
_ 20  _  40 _  10
_  _ _  _  10 _     

origen=0
dijkstra 0 15 40 20 10 10
         0  1  2  3  4  5







Coste del taxi = 20

tren                avion
(0)------------------(3)
 |        20          |
 | 5                  | 40
 |                    |
(1)------------------(4)
 |        20          |
 | 50                 | 10
 |                    |
(2)------------------(5)
          20

Para conseguir  esto se recurre a un supergrafo, colocando las matrices de costes en la diagonal
En la diagonal inversa se colocan los costes del taxi para poder cambiar de medio de circulacion en  una misma ciudad

0  1  2  3  4  5
_  5  _  20 _  _
5  _ 50  _  20 _
_  50 _  _  _  20
20 _  _  _  40 _
_  20 _  40 _  10
_  _  20 _  10 _

De esta manera se para viajar de 0 a 2 habria varios caminos diferentes:
 0tren-1tren-2tren
 0tren-1tren-2avion
 0tren-1avion-2tren
 0tren-1avion-2avion
 0avion-1tren-2tren
  ...
  Para que esto funcione con el supergrafo hay que tener en cuenta que el nodo 0 y el nodo numVert() se refieren a la misma ciudad
  El nodo 1 y el nodo numVert()+1 se refieren a la misma ciudad 
  etc...

  Si aplicamos Dijsktra a este supergrafo el vector que devuelve sera de tamaño 2*numVert() = 6 (en este caso)

  _  _  _  _  _  _
  0  1  2  3  4  5

  De la posicion 0 a la posicion 2 serian los costes minimos desde origen a cualquier ciudad en tren.
  De la posicion 3 a la posicion 5 (desde numVert() hasta 2*numVert()-1 ) serian los costes minimos desde origen
   hasta cualquier ciudad en avion.
*/
#include "GrafoP.hpp"
template<typename tCoste>
GrafoP<tCoste> SuperGrafo(GrafoP<tCoste>& g1, GrafoP<tCoste>& g2, tCoste taxi)
{
    int n = g1.numVert()+g2.numVert();
	GrafoP<tCoste> G(n);

    //Guardamos las ciudades de Fobos en el cuadrante 1 del supergrafo
	for (size_t i=0; i<g1.numVert(); i++)
		for (size_t j=0; j<g1.numVert(); j++)
			G[i][j] = g1[i][j];
    //Guardamos las ciudades de Deimos en el cuadrante 4 del supergrafo
	for (size_t i=0; i<g2.numVert(); i++)
		for (size_t j=0; j<g2.numVert(); j++)
			G[i+g1.numVert()][j+g1.numVert()] = g2[i][j];
    for(size_t i=0;i<g1.numVert();++i)
    {
            G[i][g1.numVert()+i]=taxi;
            G[g1.numVert()+i]=taxi;
    }
    return G;
}

/*
A
  0 1 2
0 0 4 6
1 4 0 5
2 6 5 0
bus
Dijkstra(0)  _ _ _

B
  0 1 2
0 0 8 1
1 8 0 2
2 1 2 0
tren
Dijkstra(0) _ _ _
taxi=x

Supergrafo (6x6)

  0 1 2 3 4 5
0 0 4 6 x
1 4 0 5   x
2 6 5 0     x
3 x     0 8 1
4   x   8 0 2
5     x 1 2 0

viajar de 1 a 2 en bus 5
Cambiar a taxi 2 a 5 x
viajar de 5 a 3 en tren


Dijktra(0) _ _ _ _ _ _
           0 1 2 3 4 5
            bus   tren

   bus   tren  avion
  0 1 2 3 4 5 6 7 8
0 0 4 6 x     y
1 4 0 5   x     y
2 6 5 0     x     y
3 x     0 8 1 y
4   x   8 0 2   y
5     x 1 2 0     y
6 y     y     1 0 4
7   y     y    3 2 1 
8     y     y  1 5 3


*/
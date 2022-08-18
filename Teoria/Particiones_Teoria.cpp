/*
Vector de pertenencia: encontrar € O(1)
                        unir € O(n)

Listas de elementos: encontrar € O(1)
                        unir € O(n) , tiempo ejecucion < tiempo ejecucion(Vector de pertenencia)

Listas de elementos con longitud:  encontrar € O(1)
                        unir € O(n) , tiempo ejecucion se reduce a la mitad como minimo

Bosque de arboles: encontrar € O(n)
                        unir € O(1)

Bosque de arboles con control de altura: encontrar € O(logn)
                                            unir € O(1)

Bosque de arboles con control de altura y compresion de caminos: encontrar € O(1)
                                                                    unir € O(n)
Nótese que con esta mejora el coste de una operación en el peor caso sigue siendo O(n), 
ya que seguimos pudiendo generar cadenas arbitrariamente largas, 
aunque después se compriman cuando las recorremos. 
Sin embargo, el coste amortizado de una operación, es decir, 
el coste promedio de las operaciones dentro de una secuencia de operaciones, es mucho menor.                                                                   

La compresión de caminos, es una forma de aplanar la estructura del árbol cuando se aplique Buscar. 
La idea es que cada nodo visitado en el camino hacia la raíz puede ser añadido directamente a la raíz;
todos ellos comparten el mismo representante. 
Para lograr este efecto, mientras Buscar recursivamente se mueve hacia la raíz, 
este cambia la referencia del padre del nodo a la raíz que encuentre. 
El árbol resultante es más aplanado, acelerando operaciones futuras no solo en estos elementos 
sino también en aquellos que referencian a estos.
*/
/*

0----1----2


3---4


{{0,1,2}{3,4}}








*/
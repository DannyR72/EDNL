#include "..\Implementaciones\particion_vpertenencia.hpp"
#include<iostream>
using namespace std;
int main()
{
    Particion_pertenencia p(10);
    p.mostrarVector();
    p.unir(7,2);
    p.unir(7,3);
    p.unir(4,0);
    p.unir(1,6);
    p.unir(1,8);
    p.unir(1,9);
    cout << endl;
    p.mostrarVector();
    p.unir(4,1);
    cout << endl;
    p.mostrarVector();
}
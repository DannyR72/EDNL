#include<vector>
#include<iostream>
/*
En el momento de unir dos elementos se trabaja exclusivamente con representantes
*/
class Particion_pertenencia 
{
    public:
        Particion_pertenencia(int n): padre(n)
        {
            for(int i=0;i<padre.size();++i)
                padre[i]=i;
        }
        void unir(int a, int b);
        int encontrar(int x) const;
        void mostrarVector() const;
    private:
        mutable std::vector<int> padre;
};

void Particion_pertenencia::unir(int a, int b) 
{
    for(int i=0;i<padre.size();++i)
    {
        if(padre[i]==b)
            padre[i]=a;
    }
}
int Particion_pertenencia::encontrar(int a) const
{
    return padre[a];
}
void Particion_pertenencia::mostrarVector() const
{
    for(int i=0;i<padre.size();++i)
    {
        std::cout << padre[i] << ",";
    }
}

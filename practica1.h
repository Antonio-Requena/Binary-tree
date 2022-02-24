#ifndef PRACTICA1_H
#define PRACTICA1_H

#include "abin.h"

template <typename T>
unsigned n_nodos(const Abin<T>& A)
{
    return contar_nodos(A,A.raiz());
}

template <typename T>
unsigned contar_nodos(const Abin<T>& Arbol, const typename Abin<T>::nodo &n)
{
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else 
        return 1 + contar_nodos(Arbol,Arbol.hijoIzqdo(n)) + contar_nodos(Arbol,Arbol.hijoDrcho(n));
}


template <typename T>
unsigned altura_recur(const Abin<T>& Arbol, const typename Abin<T>::nodo &n)
{
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else 
        return 1 + maximo(altura_recur(Arbol,Arbol.hijoIzqdo(n)),altura_recur(Arbol,Arbol.hijoDrcho(n)));
}

template <typename T>
unsigned altura_arbol(const Abin<T> & A) //Función llamadora de la función recursiva
{
    assert (!A.arbolVacio());
    return (altura_recur(A,A.raiz()) - 1);
}

template <typename T>
unsigned profundidad_rec(const Abin<T>& Arbol, const typename Abin<T>::nodo &n)
{
    if(Arbol.padre(n) == Abin<T>::NODO_NULO)
        return 0;
    else
        return 1 + profundidad_rec(Arbol, Arbol.padre(n));
}

template <typename T>
unsigned profundidad(const Abin<T>& A, const typename Abin<T>::nodo &n)
{
    assert(!A.arbolVacio());
    return profundidad_rec(A,n);
}




#endif
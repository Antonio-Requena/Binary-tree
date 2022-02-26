#ifndef PRACTICA1_HPP
#define PRACTICA1_HPP

#include <iostream>
#include "abin.h"

//Practica terminada
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
int altura_recur(const Abin<T>& Arbol, const typename Abin<T>::nodo &n)
{
    if (n == Abin<T>::NODO_NULO)
        return -1;
    else 
        return 1 + std::max(altura_recur(Arbol,Arbol.hijoIzqdo(n)),altura_recur(Arbol,Arbol.hijoDrcho(n)));
}

template <typename T>
int altura_arbol(const Abin<T> & A) //Función llamadora de la función recursiva
{
    assert (!A.arbolVacio());
    return altura_recur(A,A.raiz());
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

template <typename T>
int desequilibrio(const Abin<T>& A)
{
    if (A.arbolVacio())
        return -1;
    else
        return std::abs(A.altura_nodo(A.hijoIzqdo(A.raiz())) - A.altura_nodo(A.hijoDrcho(A.raiz())));
}

template <typename T>
bool pseudocompleto(const Abin<T>& A)
{
    assert(!A.arbolVacio());
    return pseudocompletoRec(A.raiz(), A);
}

template <typename T>
bool pseudocompletoRec(const typename Abin<T>::nodo &n, const Abin<T>& A)
{
    if(n == Abin<T>::NODO_NULO)
        return true;
    else if(profundidad(A,n) == altura_arbol(A)- 1)
        {
            if((A.hijoIzqdo(n)!= Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO) || (A.hijoIzqdo(n)== Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO))
                return false;
            else 
                return true;
        }
        else
            return (pseudocompletoRec(A.hijoIzqdo(n),A) && pseudocompletoRec(A.hijoDrcho(n),A));
}

#endif
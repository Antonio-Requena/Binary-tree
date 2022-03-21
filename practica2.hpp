#ifndef PRACTICA2_HPP
#define PRACTICA2_HPP

#include "abin.h"

template <typename T>
bool ArbolesSimilares(const Abin<T>& A, const Abin<T>& B)
{
    return SimilaresRec(A, A.raiz(),B,B.raiz());
}

template <typename T>
bool SimilaresRec(const Abin<T>& A, const typename Abin<T>::nodo &nodoA, const Abin<T>& B, const typename Abin<T>::nodo &nodoB)
{
    if(nodoA == Abin<T>::NODO_NULO && nodoB == Abin<T>::NODO_NULO)
        return true;
    else if(nodoA == Abin<T>::NODO_NULO || nodoB == Abin<T>::NODO_NULO)
            return false;
        else
            return (SimilaresRec(A, A.hijoIzqdo(nodoA),B,B.hijoIzqdo(nodoB)) && SimilaresRec(A, A.hijoDrcho(nodoA),B,B.hijoDrcho(nodoB))); 
    
}

template <typename T>
Abin<T> ArbolReflejado(const Abin<T>& A)
{
    Abin<T> Copia;
    if(!A.arbolVacio())
    {
        Copia.insertarRaiz(A.raiz()->elto);
        ReflejadoRec(A,Copia,A.raiz(),Copia.raiz());
    }
    return Copia;
    
    
}

template <typename T>
void ReflejadoRec(const Abin<T>& A, Abin<T>& Copia, const typename Abin<T>::nodo &nodoA, const typename Abin<T>::nodo &nodocopia)
{
    
    if(A.hijoIzqdo(nodoA) != Abin<T>::NODO_NULO)
    {
        Copia.insertarHijoDrcho(nodocopia, A.hijoIzqdo(nodoA)->elto);
        ReflejadoRec(A,Copia,A.hijoIzqdo(nodoA),Copia.hijoDrcho(nodocopia));
    }     
    if(A.hijoDrcho(nodoA) != Abin<T>::NODO_NULO)
    {
        Copia.insertarHijoIzqdo(nodocopia, A.hijoDrcho(nodoA)->elto);
        ReflejadoRec(A,Copia,A.hijoDrcho(nodoA),Copia.hijoIzqdo(nodocopia));
            
    }
}

//**// Ejercicio 3 //**//

struct T_ArbExpresion
{
    char op;
    float operando;
};

float ResultadoRec(const Abin<T_ArbExpresion>& A, const typename Abin<T_ArbExpresion>::nodo &n)
{
    if(A.hijoDrcho(n) == Abin<T_ArbExpresion>::NODO_NULO && A.hijoIzqdo(n) == Abin<T_ArbExpresion>::NODO_NULO)
        return A.elemento(n).operando;
    else
    {
        switch (A.elemento(n).op)
        {
        case '+':
            return ResultadoRec(A,A.hijoIzqdo(n)) + ResultadoRec(A,A.hijoDrcho(n));
            break;
        case '-':
            return ResultadoRec(A,A.hijoIzqdo(n)) - ResultadoRec(A,A.hijoDrcho(n));
            break;
        case '*':
            return ResultadoRec(A,A.hijoIzqdo(n)) * ResultadoRec(A,A.hijoDrcho(n));
            break;
        case '/':
            return ResultadoRec(A,A.hijoIzqdo(n)) / ResultadoRec(A,A.hijoDrcho(n));
            break;
        default:
            break;
        }
    }
}

float Resultado(const Abin<T_ArbExpresion>& A)
{
    return ResultadoRec(A,A.raiz());
}


#endif
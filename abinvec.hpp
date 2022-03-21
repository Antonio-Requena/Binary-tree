#ifndef ABINVEC_HPP
#define ABINVEC_HPP
#include <cassert>
#include <math.h>

template <typename T> class Abin 
{ 
public:
    typedef size_t nodo; // índice del vector, // entre 0 y maxNodos-1
    static const nodo NODO_NULO;

    explicit Abin(int AlturaMax, const T& e_nulo = T()); 
    void insertarRaiz(const T& e);
    void insertarHijoIzqdo(nodo n, const T& e); 
    void insertarHijoDrcho(nodo n, const T& e);
    
    bool arbolVacio() const;

    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hijoDrcho(nodo n) const;

private:
    T* nodos; // vector de nodos 
    size_t maxNodos; // tamaño del vector
    size_t H;       //Altura maxima del arbol
    T ELTO_NULO; // marca celdas vacías

    int Altura_nodo(nodo n);
    int profundidad(nodo n) const;
};

//Funcion para calcular el tamaño del vector en funcion de una altura máxima
inline int N(int H){ return (pow(2,H+1) - 1);}

/* Definición del nodo nulo */

template <typename T>
const typename Abin<T>::nodo Abin<T>::NODO_NULO(SIZE_MAX);

/* Metodos Publicos*/

template <typename T>
Abin<T>::Abin(int AlturaMax, const T& e_nulo) :
    H(AlturaMax),
    nodos(new T[N(AlturaMax)]),
    maxNodos(N(AlturaMax)),
    ELTO_NULO(e_nulo)
{
    for (nodo n = 0; n <= maxNodos-1; n++) // Marcar todas las celdas libres.
        nodos[n] = ELTO_NULO;
}

template <typename T>
void Abin<T>::insertarRaiz(const T& e)
{
    assert(nodos[maxNodos/2] == ELTO_NULO);
    nodos[maxNodos/2] = e;
}

template <typename T>
void Abin<T>::insertarHijoIzqdo(const typename Abin<T>::nodo n, const T& e)
{
    int h = H - profundidad(n);
    int i = n-pow(2,h-1);
    assert(nodos[i] == ELTO_NULO);
    nodos[i] = e;
}

template <typename T>
void Abin<T>::insertarHijoDrcho(const typename Abin<T>::nodo n, const T& e)
{
    int h = H - profundidad(n);
    int i = n+pow(2,h-1);
    assert(nodos[i] == ELTO_NULO);
    nodos[i] = e;
}

template <typename T>
inline typename Abin<T>::nodo Abin<T>::raiz() const 
{
    return (nodos[maxNodos/2] == ELTO_NULO) ? NODO_NULO : maxNodos/2; 
}

template <typename T>
typename Abin<T>::nodo Abin<T>::hijoIzqdo(const typename Abin<T>::nodo n) const
{
    int h = H - profundidad(n);
    int i = n-pow(2,h-1);
    return (nodos[i] == ELTO_NULO) ? NODO_NULO : i;
}

template <typename T>
typename Abin<T>::nodo Abin<T>::hijoDrcho(const typename Abin<T>::nodo n) const
{
    int h = H - profundidad(n);
    return (nodos[n+pow(2,h-1)] == ELTO_NULO) ? NODO_NULO : n+pow(2,h-1);
}

template <typename T>
typename Abin<T>::nodo Abin<T>::padre(const typename Abin<T>::nodo n) const
{
    if(n == raiz()) return NODO_NULO;
    else
    {
        int h = H - profundidad(n);
        size_t pot = pow(2,h+2);
        
        if(n%pot == (pow(2,h)-1))
            return (n + pow(2,h));
        else 
            return (n - pow(2,h));
    }
}

/* METODOS PRIVADOS */

template <typename T>
int Abin<T>::profundidad(const typename Abin<T>::nodo n) const
{
    if(n == raiz())
        return 0;
    else
        return 
}

template<typename T>
int Abin<T>::Altura_nodo(const typename Abin<T>::nodo n)
{
    
    if (n == NODO_NULO)
        return -1;
    else
        return 1+ max(Altura_nodo(hijoIzqdo(n)),Altura_nodo(hijoDrcho(n)));
}

#endif
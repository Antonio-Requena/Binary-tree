#ifndef ABIN_H
#define ABIN_H

#include <cassert>

struct celda;
template <typename T>
unsigned maximo(const T& , const T& ); 

template <typename T> class Abin {
    struct celda; // declaración adelantada privada
public:
    typedef celda* nodo;
    static const nodo NODO_NULO;
    Abin(); // constructor
    void insertarRaiz(const T& e);
    void insertarHijoIzqdo(nodo n, const T& e);
    void insertarHijoDrcho(nodo n, const T& e);
    void eliminarHijoIzqdo(nodo n);
    void eliminarHijoDrcho(nodo n);
    void eliminarRaiz();
    bool arbolVacio() const;
    const T& elemento(nodo n) const; // acceso a elto, lectura 
    T& elemento(nodo n); // acceso a elto, lectura/escritura 
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hijoDrcho(nodo n) const;
    Abin(const Abin<T>& a); // ctor. de copia 
    Abin<T>& operator =(const Abin<T>& A); // asig.de árboles 
    unsigned profundidad_nodo(nodo n) const; 
    int altura_nodo(nodo n) const; 
    ~Abin(); // destructor
private:
    struct celda {
        T elto;
        nodo padre, hizq, hder;
        celda(const T& e, nodo p = NODO_NULO): elto(e),
        padre(p), hizq(NODO_NULO), hder(NODO_NULO) {} 
    };
    nodo r;   // nodo raíz del árbol
    void destruirNodos(nodo& n);
    nodo copiar(nodo n);
    unsigned profundidad_rec(nodo &n);
    int altura_recursiva(nodo& n) const;
};
/* Definición del nodo nulo */
template <typename T>
const typename Abin<T>::nodo Abin<T>::NODO_NULO(NULL);

/*-------------------------*/ /* Métodos públicos */ /*-------------------------*/
template <typename T>
inline Abin<T>::Abin() : r(NODO_NULO) {}

template <typename T>
inline void Abin<T>::insertarRaiz(const T& e) {
   assert(r == NODO_NULO);   // Árbol vacío
   r = new celda(e);
}

template <typename T>
inline void Abin<T>::insertarHijoIzqdo(nodo n, const T& e) {
    assert(n != NODO_NULO);
    assert(n->hizq == NODO_NULO); // No existe hijo izqdo.
    n->hizq = new celda(e, n);
}
template <typename T>
inline void Abin<T>::insertarHijoDrcho(nodo n, const T& e) {
    assert(n != NODO_NULO);
    assert(n->hder == NODO_NULO); // No existe hijo drcho. 
    n->hder = new celda(e, n);
}
template <typename T>
inline void Abin<T>::eliminarHijoIzqdo(nodo n) {
    assert(n != NODO_NULO);
    assert(n->hizq != NODO_NULO); // Existe hijo izqdo.
    assert(n->hizq->hizq == NODO_NULO && // Hijo izqdo.
            n->hizq->hder == NODO_NULO); // es hoja.
    delete n->hizq;
    n->hizq = NODO_NULO;
}
template <typename T>
inline void Abin<T>::eliminarHijoDrcho(nodo n) {
    assert(n != NODO_NULO);
    assert(n->hder != NODO_NULO); // Existe hijo drcho.
    assert(n->hder->hizq == NODO_NULO &&
            n->hder->hder == NODO_NULO);
    delete n->hder;
    n->hder = NODO_NULO;
}
template <typename T>
inline void Abin<T>::eliminarRaiz()
{
    assert(r != NODO_NULO);   // Árbol no vacío.
    assert(r->hizq == NODO_NULO &&
    r->hder == NODO_NULO); delete r;
    r = NODO_NULO;
}
template <typename T> inline bool Abin<T>::arbolVacio() const { return (r == NODO_NULO); }
template <typename T>
inline const T& Abin<T>::elemento(nodo n) const 
{
    assert(n != NODO_NULO);
    return n->elto; 
}

template <typename T>
inline T& Abin<T>::elemento(nodo n)
{
   assert(n != NODO_NULO);
   return n->elto;
}

template <typename T>
inline typename Abin<T>::nodo Abin<T>::raiz() const { return r; }

template <typename T> inline
typename Abin<T>::nodo Abin<T>::padre(nodo n) const 
{
   assert(n != NODO_NULO);
   return n->padre;
}

template <typename T> inline
typename Abin<T>::nodo Abin<T>::hijoIzqdo(nodo n) const 
{
   assert(n != NODO_NULO);
   return n->hizq;
}

template <typename T> inline
typename Abin<T>::nodo Abin<T>::hijoDrcho(nodo n) const 
{
   assert(n != NODO_NULO);
   return n->hder;
}

template <typename T>
inline Abin<T>::Abin(const Abin<T>& A)
{
    r = copiar(A.r); // Copiar raíz y descendientes. 
}
template <typename T>
Abin<T>& Abin<T>::operator =(const Abin<T>& A) {
    if (this != &A) // Evitar autoasignación. 
    {
        this->~Abin();   // Vaciar el árbol.
        r = copiar(A.r); // Copiar raíz y descendientes. 
    }
   return *this;
}

template <typename T>
inline Abin<T>::~Abin()
{
   destruirNodos(r);   // Vaciar el árbol.
}

template <typename T>
unsigned maximo(const T& a, const T& b) 
{
    return (a >= b) ? a : b;
}

template <typename T>
unsigned Abin<T>::profundidad_nodo(nodo n) const
{
    assert(r != NODO_NULO);
    return profundidad_rec(n);
}

template <typename T>
int Abin<T>::altura_nodo(nodo n) const
{
    assert(r != NODO_NULO); // Arbol no vacio
    return altura_recursiva(n);
}

/*--------------------------------------------------------*/ /* Métodos privados */ /*--------------------------------------------------------*/ // Destruye un nodo y todos sus descendientes
template <typename T>
void Abin<T>::destruirNodos(nodo& n) {
   if (n != NODO_NULO)
    {
        destruirNodos(n->hizq); destruirNodos(n->hder); delete n;
        n = NODO_NULO;
    }
}

template <typename T>
typename Abin<T>::nodo Abin<T>::copiar(nodo n) 
{
    nodo m = NODO_NULO;
    if (n != NODO_NULO) {
        m = new celda(n->elto); // Copiar n.
        m->hizq = copiar(n->hizq); // Copiar subárbol izqdo. 
        if (m->hizq != NODO_NULO)
        {
            m->hizq->padre = m;
            m->hder = copiar(n->hder);
        }   // Copiar subárbol drcho. 
        if (m->hder != NODO_NULO)
        { 
            m->hder->padre = m;
        }
    }
    return m; 
}

template <typename T>
unsigned Abin<T>::profundidad_rec(nodo& n)
{
    if(n->padre == NODO_NULO)
        return 0;
    else
        return 1 + profundidad_rec(n->padre);
}

template <typename T>
int Abin<T>::altura_recursiva(nodo& n) const
{
    if(n == NODO_NULO || (n->hizq ==  NODO_NULO && n->hder == NODO_NULO))
        return 0;
    else 
        return 1 + maximo(altura_recursiva(n->hizq), altura_recursiva(n->hder));

}


#endif
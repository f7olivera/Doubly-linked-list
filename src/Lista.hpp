#include "Lista.h"
#include <iostream>

Lista::Lista() : longitud_(0), head_(nullptr), last_(nullptr)
{}

Lista::Lista(const Lista &l) : Lista()
{
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista()
{
    Nodo *actual = head_;
    while(actual != nullptr)
    {
        Nodo *tmp = actual;
        actual = actual->siguiente;
        delete tmp;
    }
}

Lista &Lista::operator=(const Lista &aCopiar)
{
    while(head_ != nullptr)
    {
        eliminar(0);
    }
    for(int i = 0; i < aCopiar.longitud_; ++i)
    {
        agregarAtras(aCopiar.iesimo(i));
    }
    return *this;
}

void Lista::agregarAdelante(const int &elem)
{
    Nodo *nuevo = new Nodo{nullptr, elem, head_};

    if(head_ == nullptr)
        last_ = nuevo;
    else
        head_->anterior = nuevo;

    head_ = nuevo;
    longitud_++;
}

void Lista::agregarAtras(const int &elem)
{
    Nodo *nuevo = new Nodo{last_, elem, nullptr};

    if(head_ == nullptr)
        head_ = nuevo;
    else if(head_->siguiente == nullptr)
        head_->siguiente = nuevo;
    if(last_ != nullptr)
        last_->siguiente = nuevo;

    last_ = nuevo;
    longitud_++;
}

void Lista::eliminar(Nat i)
{
    Nodo *actual = head_;
    for(int j = 0; j < i; ++j)
    {
        actual = actual->siguiente;
    }
    if(actual->anterior != nullptr)
        actual->anterior->siguiente = actual->siguiente;
    else
        head_ = actual->siguiente != nullptr ? actual->siguiente : head_;

    if(actual->siguiente != nullptr)
        actual->siguiente->anterior = actual->anterior;
    else
        last_ = actual->anterior != nullptr ? actual->anterior : last_;

    delete actual;
    longitud_--;
    if(longitud_ == 0)
    {
        head_ = nullptr;
        last_ = nullptr;
    }
}

int Lista::longitud() const
{
    return longitud_;
}

const int &Lista::iesimo(Nat i) const
{
    Nodo *actual = head_;
    for(int j = 0; j < i; ++j)
    {
        actual = actual->siguiente;
    }
    return actual->elem;
}

int &Lista::iesimo(Nat i)
{
    Nodo *actual = head_;
    for(int j = 0; j < i; ++j)
    {
        actual = actual->siguiente;
    }
    return actual->elem;
}

void Lista::mostrar(ostream &o)
{
    Nodo *actual = nullptr;
    o << "[";
    if (head_ != nullptr)
    {
        o << head_->elem;
        actual = head_->siguiente;
        while(actual != nullptr)
        {
            o << ", " << actual->elem;
            actual = actual->siguiente;
        }
    }
    o << "]";
}

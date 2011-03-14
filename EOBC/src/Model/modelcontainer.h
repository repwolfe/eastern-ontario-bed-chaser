#ifndef MODELCONTAINER_H
#define MODELCONTAINER_H

#include <QSet>

/**
 * A generic container class.
 * Allows you to add a type, delete a type,
 * and change the stored container.
 * Example: An area has a bunch of facilities, so you
 * can add an facility, remove a facility, or pass in
 * a collection of facilities.
 * Subclasses will specify what they hold and have any
 * additional capabilities.
 */

template<class T>
class ModelContainer
{
public:
    ModelContainer<T>();
    ModelContainer(QSet<T*>& container);
    virtual ~ModelContainer();

    void addT(T* inT);
    void deleteT(T* inT);
    void setContainer(QSet<T*>& inContainer);

protected:
    void _deleteAll();
    QSet<T*> _container;
};

// This is in the header file because template classes require
// the implementation in the same file as the definition

template<typename T>
ModelContainer<T>::ModelContainer()
{
}

template<typename T>
ModelContainer<T>::ModelContainer(QSet<T *>& container)
    : _container(container)
{

}

template<typename T>
ModelContainer<T>::~ModelContainer()
{
    _deleteAll();
}

template<typename T>
void ModelContainer<T>::addT(T* inT)
{
    _container.insert(inT);
}

template<typename T>
void ModelContainer<T>::deleteT(T* inT)
{
    // Requires 'typename' to compile
    typename QSet<T*>::iterator iter = _container.find(inT);

    if (iter != _container.end())
    {
        delete *iter;
        _container.erase(iter);
    }
}

template<typename T>
void ModelContainer<T>::setContainer(QSet<T*>& inContainer)
{
    if (_container != inContainer)
    {
        _deleteAll();
        _container = inContainer;
    }
}

template<typename T>
void ModelContainer<T>::_deleteAll()
{
    foreach(T* contained, _container)
    {
        delete contained;
    }
    _container.clear();
}

#endif // MODELCONTAINER_H

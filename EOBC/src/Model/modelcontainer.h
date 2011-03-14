#ifndef MODELCONTAINER_H
#define MODELCONTAINER_H

#include <QMap>

/**
 * A generic container class.
 * Allows you to add a type, delete a type,
 * and change the stored container.
 * Example: An area has a bunch of facilities, so you
 * can add an facility, remove a facility, or pass in
 * a collection of facilities.
 * You can also retrieve a facility by passing in the key
 * Subclasses will specify what they hold and have any
 * additional capabilities.
 */

template<class Key, class T>
class ModelContainer
{
public:
    ModelContainer<Key,T>();
    ModelContainer(QMap<Key,T*>& container);
    virtual ~ModelContainer();

    void addElement(Key& key, T* inElement);
    void deleteElement(Key& key);
    void setContainer(QMap<Key,T*>& inContainer);
    T* getElement(Key& key);

protected:
    void _deleteAll();
    QMap<Key,T*> _container;
};

// This is in the header file because template classes require
// the implementation in the same file as the definition

template<typename Key, typename T>
ModelContainer<Key,T>::ModelContainer()
{
}

template<typename Key, typename T>
ModelContainer<Key,T>::ModelContainer(QMap<Key,T*>& container)
    : _container(container)
{

}

template<typename Key, typename T>
ModelContainer<Key,T>::~ModelContainer()
{
    _deleteAll();
}

template<typename Key, typename T>
void ModelContainer<Key,T>::addElement(Key& key, T* inElement)
{
    _container.insert(key, inElement);
}

template<typename Key, typename T>
void ModelContainer<Key,T>::deleteElement(Key& key)
{
    // Requires 'typename' to compile
    typename QMap<Key,T*>::iterator iter = _container.find(key);

    if (iter != _container.end())
    {
        delete iter.value();
        _container.erase(iter);
    }
}

template<typename Key, typename T>
void ModelContainer<Key,T>::setContainer(QMap<Key,T*>& inContainer)
{
    if (_container != inContainer)
    {
        _deleteAll();
        _container = inContainer;
    }
}

template<typename Key, typename T>
void ModelContainer<Key,T>::_deleteAll()
{
    foreach(T* contained, _container)
    {
        delete contained;
    }
    _container.clear();
}

template<typename Key, typename T>
T* ModelContainer<Key, T>::getElement(Key& key)
{
    typename QMap<Key,T*>::iterator iter = _container.find(key);

    if (iter != _container.end())
    {
        return iter.value();
    }
    else
    {
        return 0;
    }
}

#endif // MODELCONTAINER_H

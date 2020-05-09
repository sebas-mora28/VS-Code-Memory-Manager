
#ifndef MEMORYMANAGER_VSPTRREMOTE_H
#define MEMORYMANAGER_VSPTRREMOTE_H

#include <iostream>

template<class T>
class VSPtrRemote{
    //Inicializar client;


    VSPtrRemote();




};

template<class T>
VSPtrRemote<T>::VSPtrRemote() {
    T* addr = (T*)malloc(sizeof(T));




}

#endif //MEMORYMANAGER_VSPTRREMOTE_H

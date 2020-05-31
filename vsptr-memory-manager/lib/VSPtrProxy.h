//
// Created by sebasmora on 20/5/20.
//

#ifndef MEMORYMANAGER_VSPTRPROXY_H
#define MEMORYMANAGER_VSPTRPROXY_H
#include <iostream>

template<class T>
class VSptrProxy{

    template<typename>
    friend class VSptr;


public:
    const VSptrProxy& operator=(const T& value) const;

    VSptrProxy& operator=(T&& value)const;


    operator T() const;


private:

    std::string id;

    inline VSptrProxy(std::string id) noexcept : id{id}{};
};

template<class T>
const VSptrProxy<T> &VSptrProxy<T>::operator=(const T &value) const {
    return *this;
}

template<class T>
VSptrProxy<T> &VSptrProxy<T>::operator=(T &&value) const {
    return }


#endif //MEMORYMANAGER_VSPTRPROXY_H

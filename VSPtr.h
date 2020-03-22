//
// Created by david on 22/3/20.
//

#ifndef VS_CODE_MEMORY_MANAGER_VSPTR_H
#define VS_CODE_MEMORY_MANAGER_VSPTR_H

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

template<class T>

class VSPtr {
private:

    T *ptr;

    string id;

public:

    T *get_ptr() {
        return ptr;
    }

    string get_id(){
        return id;
    }

    VSPtr () {
        id = "some random id generator like uuid";
        ptr = new T();
    }


//    VSPtr(const VSPtr &p) {
//        ptr = p;
//        cout << "Copia" << endl;
//    }

    ~VSPtr() {
        delete (ptr);
    }

    VSPtr &operator=(VSPtr &element) {
        cout << "Pointer to Pointer" << endl;
        ptr = element.get_ptr();
        id = element.get_id();
    }

    VSPtr &operator=(T element) {
        cout << "Pointer to Data" << endl;
        ptr = new T(element);
    }

    T &operator&() {
        return *ptr;
    }

    VSPtr<T>& operator*() {
        return *this;
    }

    static VSPtr<T> New() {
        return VSPtr<T>();
    }

};


#endif //VS_CODE_MEMORY_MANAGER_VSPTR_H

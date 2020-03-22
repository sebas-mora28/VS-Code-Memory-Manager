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

    T *get_ptr() {
        return ptr;
    }

public:
    explicit VSPtr(T *p = NULL) {
        ptr = p;
        cout << "Nuevo" << endl;
    }

    VSPtr(const VSPtr &p) {
        ptr = p.get_ptr();
        cout << "Copia" << endl;
    }

    ~VSPtr() {
        delete (ptr);
    }

    VSPtr &operator=(VSPtr &element) {
        cout << "Pointer to Pointer" << endl;
        ptr = element.get_ptr();
    }

    VSPtr &operator=(T element) {
        cout << "Pointer to Data" << endl;
        ptr = new T(element);
    }

    T &operator&() {
        return *ptr;
    }

    T *operator*() {
        return ptr;
    }

    //    static VSPtr New(){
//        VSPtr p1;
//        VSPtr p2 = p1;
//        return p2;
//    }

};


#endif //VS_CODE_MEMORY_MANAGER_VSPTR_H

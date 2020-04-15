//
// Created by sebasmora on 22/3/20.
//

#ifndef VS_CODE_MEMORY_MANAGER_LISTGC_H
#define VS_CODE_MEMORY_MANAGER_LISTGC_H

#include <iostream>
#include "../GarbageCollector/VSPtrInstance.h"



template <typename T>
class VSPtr;


/**
 * Node class implementation
 * @tparam T
 */

template <class T>
class Node{

public:

    /** Value stored in the node*/
    T value;

    /**Reference to the next node*/
    Node* next;

    /**
     * Constructor
     * @param value
     */
    explicit Node(T value):value(value), next(nullptr){}


};



/**
 * Linked List implmentation
 * @tparam T
 */
template <class T>
class ListGC {


private:

    /**Head of the linked List, holds the first node of the list */
    Node<T>* head;

    /**SIze of the linked list*/
    int size;

public:


    /**Constructor */
    ListGC();


    /**Destructor*/
    ~ListGC();


    /**Verify is the linked list is empty*/
    bool isEmpty();


    /**
     * Add a new node to the list
     * @param value
     */
    void add(T value);


    /**
     * Return the VSPtr instance with the ID given
     * @tparam Type
     * @tparam VStype
     * @param id
     * @return VSPtr instance with id given
     */
    //template<typename Type>
    VSPrtInfo* getByID(uint32_t id);




    /**
     * Remove the node that holds the VSPtr instance with the ID given
     * @tparam Type
     * @tparam VStype
     * @param id
     */
    template<typename Type>
    void remove(uint32_t id);



    /**
     * Print all the elements of the linked list
     */
    void print();
};





/********************************************************************************************************************
 *                                         Members and function class definition
 ********************************************************************************************************************/



/**
 * Constructor
 * @tparam T
 */

template<class T>
ListGC<T>::ListGC(): head(nullptr), size(0){}





/**
 * Destructor
 * @tparam T
 */
template<class T>
ListGC<T>::~ListGC(){

    // Implement methods
}



/**
 * Verify is the linked list is empty
 * @tparam T
 * @return
 */
template<class T>
bool ListGC<T>::isEmpty() {
    return head == nullptr;
}






/**
    * Add a new node to the list
    * @param value
    */
template <class T>
void ListGC<T>::add(T value) {
    if(head==nullptr){
        head = new Node<T>(value);
        //std::cout << "New Node " << value << "\n";
    }else{

        Node<T>* temp = head;

        while(temp->next != nullptr){
            temp = temp->next;

        }
        temp->next = new Node<T>(value);
        //std::cout << "NEW Node " << value << "\n";
    }
    size++;
}





/**
 * Return the VSPtr instance with the ID given
 * @tparam Type
 * @tparam VStype
 * @param id
 * @return VSPtr instance with id given
 */

template <class T>
VSPrtInfo* ListGC<T>::getByID(uint32_t id) {
    Node<T>* current = head;

    while(current != nullptr){


        VSPrtInfo* vsPrtInfo = current->value;

        if(vsPrtInfo->id == id){
            return vsPrtInfo;
        }
        current = current->next;

    }
}





/**
 * Remove the node that holds the VSPtr instance with the ID given
 * @tparam Type
 * @tparam VStype
 * @param id
 */
template <class T>
template<typename Type>
void ListGC<T>::remove(uint32_t id) {

    if(!isEmpty()){

        Node<T>* current = head;
        Node<T>* prev = head;


        VSPtrInstance<Type>* currentVSPinstance = static_cast<VSPtrInstance<Type>*>(current->value);
        VSPtrInstance<Type>* prevVSPinstance = static_cast<VSPtrInstance<Type>*>(prev->value);


        if(prevVSPinstance->getId() == id) {
            head = current->next;
            delete(current);
            return;

        }

        while(currentVSPinstance->value != id) {
            prev = current;
            current = current->next;
            currentVSPinstance = static_cast<VSPtrInstance<Type>>(current->value);
        }

        prev->next = current->next;
        delete(current);
    }

}



/**
   * Print all the elements of the linked list
   */
template<class T>
void ListGC<T>::print() {
    std::cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" <<"\n";
    Node<T>* temp = head;
    while(temp != nullptr){
        //VSPrtInfo* vsPrtInfo = temp->value;
        //std::cout << "INSTANCIA  " << vsPrtInfo->getInstance() << "   id " << vsPrtInfo->id << "   REF COUNT " <<  vsPrtInfo->refcount << "\n";
        std::cout << temp->value << "\n";
        temp = temp->next;

    }
    std::cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" <<"\n";


}


#endif //VS_CODE_MEMORY_MANAGER_LISTGC_H

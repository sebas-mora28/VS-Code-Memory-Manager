#ifndef GC_LISTGC_H
#define GC_LISTGC_H

#include <iostream>







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
    template<typename Type, typename VStype>
    VSPtr<T> getByID(uint32_t id);




    /**
     * Remove the node that holds the VSPtr instance with the ID given
     * @tparam Type
     * @tparam VStype
     * @param id
     */
    template<typename Type, typename VStype>
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
        std::cout << "New Node " << value << "\n";
    }else{

        Node<T>* temp = head;

        while(temp->next != nullptr){
            temp = temp->next;

        }
        temp->next = new Node<T>(value);
        std::cout << "NEW Node " << value << "\n";
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
template<typename Type, typename VStype>
VSPtr<T> ListGC<T>::getByID(uint32_t id) {
    Node<T>* current = head;

    while(current != nullptr){
        VSPtrInstance<VStype>* currentVSPinstance = static_cast<VSPtrInstance<VStype>*>(current->value);
        VSPtr<Type> currentVSPtr = static_cast<VSPtr<Type>>(currentVSPinstance->instance);

        if(currentVSPtr.get_id() == id){
            return current->value;
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
template<typename Type, typename VStype>
void ListGC<T>::remove(uint32_t id) {
    Node<T>* current = head;

    while(current != nullptr){
        VSPtrInstance<VStype>* currentVSPinstance = static_cast<VSPtrInstance<VStype>*>(current->value);
        VSPtr<Type> currentVSPtr = static_cast<VSPtr<Type>>(currentVSPinstance->instance);

        if(currentVSPtr.get_id() == id){
            delete *currentVSPinstance;
            delete  currentVSPinstance;
            break;

        }
        current = current->next;

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
        std::cout << "DIRECCION EN EL NODO DE LA LISTA " << temp->value << "\n";
        temp = temp->next;

    }
    std::cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" <<"\n";


}


#endif //GC_LISTGC_H

//
// Created by sebasmora on 22/3/20.
//


#ifndef GC_VSPOINTER_H
#define GC_VSPOINTER_H

#include <iostream>
#include "../GarbageCollector/GarbageCollector.h"
#include "../Client/RemoteMemory.h"
#include <typeinfo>

template<class T>
class VSPtr{

    /**
     * CLASS MEMBERS
     */
private:
    T *addr;
    std::string id;
    bool is_remote = false;



    /**
    * Returns the current of the current VSPtr
    * @tparam T
    * @return string id
    */
    std::string get_id();




    /**
    * Returns the addr store by the VSPtr
    * @tparam T
    * @return
    */
    T* get_ptr();


    
    /**
     * Adds new VSPtr instance locally
     */
    void addInstanceLocally();
    
    
    /**
     * Adds new VSptr instance remotely
     */
    void addInstanceRemotely();


    /**
     * Sets VSPtr's id generated it by garbageCollector
     */
     void setVSPtrIdFromGarbageCollector();



    /**
     * Decrements Ref Count locally
     */
     void decrementRefCountLocally(std::string id);



     /**
      * Decrements Ref Count remotely
      */
      void decrementRefCountRemotely(std::string id);



      /**
       * Increments Ref Count Locally
       */
       void incrementRefCountLocally(std::string id);


       /**
        * Decrements Ref Count remotely
        */
        void incrementRefCountRemotely(std::string id);



public:


 

/**
     * Constructor
     */
    explicit VSPtr(bool is_remote) {
        printf("Constructor\n");
        std::cout << (is_remote ? "Remoto" : "Local") << "\n";
        is_remote ? addInstanceRemotely() : addInstanceLocally();
    }


    
    
    
    /**
     * Copy constructor
     * @param p
     */

    VSPtr(const VSPtr& other) {
        std::cout << other.id << "\n";
        addr = other.addr;
        printf("Copia \n");
    }





    /**
     * Destructor
     */

    ~VSPtr() {
        this->is_remote ? decrementRefCountRemotely(id) : decrementRefCountLocally(id);

    }



    /****************************************************************************************************************
     *                                          OPERATORS OVERLOAD
     ****************************************************************************************************************/



    /**
     * Overload = operator
     * @param other
     * @return
     */
    VSPtr<T>& operator=(VSPtr<T>& other) {
        printf("Pointer to Pointer %d \n", other.is_remote);
        this->is_remote ? decrementRefCountRemotely(id) : decrementRefCountLocally(id);
        addr = other.get_ptr();
        id = other.get_id();
        other.is_remote ? incrementRefCountRemotely(id) : incrementRefCountLocally(id);
        GarbageCollector::getGarbageCollectorInstance()->printGargabeCollectorInfo();
        return *this;
    }



    /**
     * Overlodad the = operator
     * @param element
     * @return
     */
    void operator=(T element) {
        if(!is_remote){
            *addr = element;
        }else{
            RemoteMemory::getInstance()->setValue(element, id);
        }
    }






    /**
     * Overlodad & operato
     * @return
     */
    T& operator&() {
        return *addr;
    }






    /**
     * Overload the * operator
     * @return
     */
    VSPtr &operator*(){
        return *this;
    }





    /*****************************************************************************************************************
     *                              VSPointer's  initializers
     ****************************************************************************************************************/



    /**
     * Local VSPtr initialization
     * @return
     */
     static VSPtr<T> New() {
        VSPtr<T> newVSptr {VSPtr<T>(false)};
        return newVSptr;
    }


    /**
     * Remote VSptr initialization
     */
     static VSPtr<T> NewRemote(){
         VSPtr<T> newVSptr {VSPtr<T>(true)};
         return newVSptr;
     }

};



/******************************************************************************************************************
 *                                  Methods definitions
 *****************************************************************************************************************/





/**
 * Returns the current of the current VSPtr
 * @tparam T
 * @return string id
 */
template<class T>
std::string VSPtr<T>::get_id() {
        return this->id;
}




/**
    * Returns the addr store by the VSPtr
    * @tparam T
    * @return
    */
template<class T>
T *VSPtr<T>::get_ptr() {
    if(is_remote){
    }
    return this->addr;
}






/**
 * Adds new VSPtr instance locally
 * @tparam T
 */
template<class T>
void VSPtr<T>::addInstanceLocally() {
    this->is_remote = false;
    addr = new T{};
    setVSPtrIdFromGarbageCollector();
    GarbageCollector::getGarbageCollectorInstance()->addInstance(addr, id);
    GarbageCollector::getGarbageCollectorInstance()->printGargabeCollectorInfo();
    std::cout << "DIRECCION DE MEMORIA DEL DATO QUE GUARDA EL VSPointer  " << get_id() << "   " << addr << "\n\n";

}







/**
 * Adds new VSPtr instance remotely
 * @tparam T
 */
template<class T>
void VSPtr<T>::addInstanceRemotely() {
    this->is_remote = true;
    const char* name = typeid(T).name();
    this->id = GarbageCollector::getGarbageCollectorInstance()->generateID();
    RemoteMemory::getInstance()->remoteAddInstance(name, id);
    std::cout << "El id es " << id << "\n";



}

/**
 * Sets VSPtr's id generated it by garbageCollector
 * @tparam T
 */

template<class T>
void VSPtr<T>::setVSPtrIdFromGarbageCollector() {
    this->id = GarbageCollector::getGarbageCollectorInstance()->generateID();

}



/**
 * Decrements VSPtr ref count locally
 * @tparam T
 * @param id
 */

template<class T>
void VSPtr<T>::decrementRefCountLocally(std::string id) {
    GarbageCollector::getGarbageCollectorInstance()->decrementRedCount(id);
}



/**
 * Decrements VSPtr ref count remotely
 * @tparam T
 * @param id
 */
template<class T>
void VSPtr<T>::decrementRefCountRemotely(std::string id) {
    RemoteMemory::getInstance()->remoteDecremetnInstance(id);

}



/**
 * Increments VSPtr ref count locally
 * @tparam T
 * @param id
 */
template<class T>
void VSPtr<T>::incrementRefCountLocally(std::string id) {
    GarbageCollector::getGarbageCollectorInstance()->incrementRefCount(id);

}



/**
 * Increments VSPtr ref count remotely
 * @tparam T
 * @param id
 */
template<class T>
void VSPtr<T>::incrementRefCountRemotely(std::string id) {
    RemoteMemory::getInstance()->remoteIncrementInstance(id);
}



#endif //GC_VSPOINTER_H

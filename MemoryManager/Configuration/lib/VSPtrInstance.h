//
// Created by sebasmora on 22/3/20.
//

#ifndef GC_VSPTRINSTANCE_H
#define GC_VSPTRINSTANCE_H

#include <iostream>
#include <sstream>

/**
 * VSPtr class, this class holds the reference count of each VSPtr instance
 */
class VSPrtInfo {


public:
    std::string id;
    int refcount;
    std::string type;

    virtual void* getAdress() = 0;
    virtual std::string getValue() = 0;


    virtual ~VSPrtInfo() {
    };
};

/**
 * Struct that holds a VSPtr
 * @tparam T
 */
template <typename T>
class VSPtrInstance: public VSPrtInfo{

private:
    /**VSPtr instance*/
    T instance;


    /**
     * VSPtr constructor
     * @param instance VSPtr instance
     */

public:
    explicit VSPtrInstance(T instance, std::string& id);


    /**
    * This method return that VSPtr instance that holds VSPtrInstance
    * @tparam T
    * @return
    */
    //T getAdress();
    void* getAdress() override {
        return instance;
    };


    std::string getValue() override {
        std::stringstream str;
        str << (*instance);
        return str.str();
    }




    /**
     * Get the data type of current instance
     * @param type
     * @return
     */
    std::string getTypeData(T& type);



    /**
    * This method add a new instance to the garbage collector list
    * @tparam T
    * @param instance
    */
    ~VSPtrInstance();


};

/********************************************************************************************************************
 *                                         Members and function class definition
 ********************************************************************************************************************/



/**
* This method add a new instance to the garbage collector list
* @tparam T
* @param instance
*/
template<typename T>
VSPtrInstance<T>::~VSPtrInstance() {
    delete instance;
}



/**
 * This method add a new instance to the garbage collector list
 * @tparam T
 * @param instance
 */
template<typename T>
VSPtrInstance<T>::VSPtrInstance(T instance, std::string& id){
    VSPrtInfo::refcount = 1;
    VSPrtInfo::id = id;
    VSPrtInfo::type = getTypeData(instance);
    this->instance = instance;
    //std::cout << "INSTANCIA GUARDADA EN VSptrInstance " << instance << "   " << this->instance <<"   "  << "    " << type <<  "\n";
}



template<typename T>
std::string VSPtrInstance<T>::getTypeData(T &type) {
    std::string result = typeid(type).name();

    if (result == "Pv"){
        return "void";
    }else if(result == "Pi"){
        return "int";
    }else if(result == "Pb"){
        return "bool";
    }else if(result == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE"){
        return "string";
    }else if(result == "Pc"){
        return "char";
    }else if(result == "Pf"){
        return "float";
    }else if(result == "Pl"){
        return "long";
    }else{
        return result;
    }

}


#endif //GC_VSPTRINSTANCE_H

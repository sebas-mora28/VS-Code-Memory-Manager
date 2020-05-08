//
// Created by sebasmora on 22/3/20.
//

#ifndef GC_VSPTRINSTANCE_H
#define GC_VSPTRINSTANCE_H

#include <iostream>


/**
 * VSPtr class, this class holds the reference count of each VSPtr instance
 */
class VSPrtInfo{

public:
    int refcount;
    std::string id;
    std::string type;

    virtual void* getInstance(){
        return nullptr;
    };

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
    //T getInstance();
    void* getInstance() override{
        return instance;
    };


    std::string getValue() override {
        return std::to_string(*instance);
    }

    /***
     * This mehods the id
     * @return
     */
    std::string getId();


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
    std::cout << "INSTANCIA GUARDADA EN VSptrInstance " << instance << "   " << this->instance <<"   "  << "    " << type <<  "\n";
}



/**
 * This method return that VSPtr's instance that holds VSPtrInstance
 * @tparam T
 * @return
*/
template<typename T>
std::string VSPtrInstance<T>::getId() {
    return this->id;
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

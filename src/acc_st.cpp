#include "acc_st.hpp"
#include <rtt/Component.hpp>
#include <iostream>

namespace acc {

  acc_st::acc_st(std::string const& name) : TaskContext(name){
    std::cout << "acc_st constructed !" <<std::endl;
  }

  bool acc_st::configureHook(){
    std::cout << "acc_st configured !" <<std::endl;
    return true;
  }

  bool acc_st::startHook(){
    std::cout << "acc_st started !" <<std::endl;
    return true;
  }

  void acc_st::updateHook(){
    std::cout << "acc_st executes updateHook !" <<std::endl;
  }

  void acc_st::stopHook() {
    std::cout << "acc_st executes stopping !" <<std::endl;
  }

  void acc_st::cleanupHook() {
    std::cout << "acc_st cleaning up !" <<std::endl;
  }

}

/*
 * Using this macro, only one component may live
 * in one library *and* you may *not* link this library
 * with another component library. Use
 * ORO_CREATE_COMPONENT_TYPE()
 * ORO_LIST_COMPONENT_TYPE(acc_st)
 * In case you want to link with another library that
 * already contains components.
 *
 * If you have put your component class
 * in a namespace, don't forget to add it here too:
 */
ORO_CREATE_COMPONENT(acc::acc_st)

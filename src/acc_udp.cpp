#include "acc_udp.hpp"
#include <rtt/Component.hpp>
#include <iostream>

namespace acc {

  acc_udp::acc_udp(std::string const& name) : TaskContext(name){
    std::cout << "acc_udp constructed !" <<std::endl;
  }

  bool acc_udp::configureHook(){
    std::cout << "acc_udp configured !" <<std::endl;
    return true;
  }

  bool acc_udp::startHook(){
    std::cout << "acc_udp started !" <<std::endl;
    return true;
  }

  void acc_udp::updateHook(){
    std::cout << "acc_udp executes updateHook !" <<std::endl;
  }

  void acc_udp::stopHook() {
    std::cout << "acc_udp executes stopping !" <<std::endl;
  }

  void acc_udp::cleanupHook() {
    std::cout << "acc_udp cleaning up !" <<std::endl;
  }

}

/*
 * Using this macro, only one component may live
 * in one library *and* you may *not* link this library
 * with another component library. Use
 * ORO_CREATE_COMPONENT_TYPE()
 * ORO_LIST_COMPONENT_TYPE(acc_udp)
 * In case you want to link with another library that
 * already contains components.
 *
 * If you have put your component class
 * in a namespace, don't forget to add it here too:
 */
ORO_CREATE_COMPONENT(acc::acc_udp)

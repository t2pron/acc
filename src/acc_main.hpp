#ifndef OROCOS_ACC_MAIN_HPP
#define OROCOS_ACC_MAIN_HPP

#include <rtt/RTT.hpp>

namespace acc {

  class acc_main : public RTT::TaskContext{
  public:
    acc_main(std::string const& name);
    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();
  };

}
#endif

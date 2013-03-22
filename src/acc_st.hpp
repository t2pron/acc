#ifndef OROCOS_ACC_ST_HPP
#define OROCOS_ACC_ST_HPP

#include <rtt/RTT.hpp>

namespace acc {

  class acc_st : public RTT::TaskContext{
  public:
    acc_st(std::string const& name);
    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();
  };

}
#endif

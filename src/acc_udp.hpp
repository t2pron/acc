#ifndef OROCOS_ACC_UDP_HPP
#define OROCOS_ACC_UDP_HPP

#include <rtt/RTT.hpp>

namespace acc {

  class acc_udp : public RTT::TaskContext{
  public:
    acc_udp(std::string const& name);
    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();
  };

}
#endif

#ifndef OROCOS_ACC_CG_HPP
#define OROCOS_ACC_CG_HPP

#include <rtt/RTT.hpp>
#include "ConstraintGeometry.hpp"

#include <acc/typekit/Types.hpp>

using namespace RTT;

namespace acc {

  class acc_cg : public RTT::TaskContext{

    //Orocos Ports
    OutputPort<acc::CGmsg> port_cg_;
    acc::CGmsg cg_;

    //Orocos Properties
    std::string filename1_;
    std::string filename2_;

    // mmaps
    ConstraintGeometry *map1_; 
    ConstraintGeometry *map2_; 
    int fd1_;
    int fd2_;
    int fileSize1_;
    int fileSize2_;
    int currentFile_;

  public:
    acc_cg(std::string const& name);
    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();
  };

}
#endif

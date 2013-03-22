#
# The find_package macro for Orocos-RTT works best with
# cmake >= 2.6.3
#
cmake_minimum_required(VERSION 2.6.3)

#
# This creates a standard cmake project. You may extend this file with
# any cmake macro you see fit.
#
project(acc)

set (ROS_ROOT $ENV{ROS_ROOT} )
if (ROS_ROOT)
  include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)
  rosbuild_init()
  rosbuild_find_ros_package( rtt )
  set( RTT_HINTS HINTS ${rtt_PACKAGE_PATH}/../install )
endif()

rosbuild_genmsg()
rosbuild_include(rtt_rosnode GenerateRTTtypekit )
ros_generate_rtt_typekit(acc)

# Use 'source orocos_toolchain/env.sh' if the command below fails:
find_package(OROCOS-RTT REQUIRED ${RTT_HINTS})

# Defines the orocos_* cmake macros. See that file for additional
# documentation.
include( ${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake )

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

orocos_component(acc_main src/acc_main.hpp src/acc_main.cpp) # ...you may add multiple source files
orocos_component(acc_udp src/acc_udp.hpp src/acc_udp.cpp)
orocos_component(acc_st src/acc_st.hpp src/acc_st.cpp)
orocos_component(acc_cg src/acc_cg.hpp src/acc_cg.cpp)

orocos_install_headers(src/acc_main.hpp src/acc_udp.hpp src/acc_st.hpp src/acc_cg.hpp src/ConstraintGeometry.hpp) # ...you may add multiple header files

target_link_libraries(acc_cg rtt-acc-typekit )

#
# Generates and installs our package. Must be the last statement such
# that it can pick up all above settings.
#
orocos_generate_package()

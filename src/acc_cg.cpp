#include "acc_cg.hpp"
#include <rtt/Component.hpp>
#include <rtt/os/TimeService.hpp>

//mmap
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

using namespace RTT;

namespace acc {

  acc_cg::acc_cg(std::string const& name) : TaskContext(name), filename1_(""), filename2_(""), currentFile_(1) {
    //Orocos Ports
    this->addPort("ConstraintGeometry", port_cg_);

    //Orocos Properties
    this->addProperty("filename1", filename1_);
    this->addProperty("filename2", filename2_);
  }

  bool acc_cg::configureHook(){

    ConstraintGeometry cg;
    cg.vertices.push_back(1);
    cg.vertices.push_back(2);
    cg.vertices.push_back(3);
    cg.triangles.push_back(1);
    cg.triangles.push_back(2);
    cg.triangles.push_back(3);

    std::cout << "CG size: " << sizeof(cg) << std::endl;
    std::cout << "Ind size" << 3*sizeof(float) + 3*sizeof(long) << std::endl;

    //Open files for writing
    if (filename1_.compare("") != 0 && filename2_.compare("") != 0) {
      fd1_ = open(filename1_.c_str(), O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
      fd2_ = open(filename2_.c_str(), O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
      if (fd1_ == -1 || fd2_ == -1) {
	perror("Error opening file for writing");
	exit(EXIT_FAILURE);
      }
    }
    else {
      perror("Filename was not specified");
      exit(EXIT_FAILURE);
    }
    return true;
  }

  bool acc_cg::startHook(){
    return true;
  }

  void acc_cg::updateHook(){

    //if recieved CORBA
    if (1) {      

      //if first file, write to second
      if (currentFile_ == 1) {

	//Calculate filesize

	//Stretch file to the necessary size    
	if (lseek(fd2_, fileSize2_-1, SEEK_SET) == -1) {
	  close(fd2_);
	  perror("Error calling lseek() to 'stretch' file 2");
	  exit(EXIT_FAILURE);
	}    
	if (write(fd2_, "", 1) != 1) {
	  close(fd2_);
	  perror("Error writing last byte of file 2");
	  exit(EXIT_FAILURE);
	}

	//Map file    
	map2_ = (ConstraintGeometry*)mmap(0, fileSize2_, PROT_READ | PROT_WRITE, MAP_SHARED, fd2_, 0);
	if (map2_ == MAP_FAILED) {
	  close(fd2_);
	  perror("Error mmapping file 2");
	  exit(EXIT_FAILURE);
	}

	//Write to file

	//Write data to message
	cg_.header.stamp.fromNSec ( RTT::os::TimeService::Instance()->getNSecs() );
	cg_.filename = filename2_;
	cg_.n = 3; // XXXX change these to read from corba
	cg_.m = 3;

	currentFile_ = 2;
      }
      //else write to first file
      else {
      	//Calculate filesize

	//Stretch file to the necessary size    
	if (lseek(fd1_, fileSize1_-1, SEEK_SET) == -1) {
	  close(fd1_);
	  perror("Error calling lseek() to 'stretch' file 1");
	  exit(EXIT_FAILURE);
	}    
	if (write(fd1_, "", 1) != 1) {
	  close(fd1_);
	  perror("Error writing last byte of file 1");
	  exit(EXIT_FAILURE);
	}

	//Map file    
	map1_ = (ConstraintGeometry*)mmap(0, fileSize1_, PROT_READ | PROT_WRITE, MAP_SHARED, fd1_, 0);
	if (map1_ == MAP_FAILED) {
	  close(fd1_);
	  perror("Error mmapping file 1");
	  exit(EXIT_FAILURE);
	}

	//Write to file

	//Write data to message
	cg_.header.stamp.fromNSec ( RTT::os::TimeService::Instance()->getNSecs() );
	cg_.filename = filename1_;
	cg_.n = 3; // XXXX change these to read from corba
	cg_.m = 3;

	currentFile_ = 1;
      }

      //Write to data port
      port_cg_.write(cg_);
    }

  }

  void acc_cg::stopHook() {
  }

  void acc_cg::cleanupHook() {
    if (munmap(map1_, fileSize1_) == -1) {
	perror("Error un-mmapping file 1");
    }
    if (munmap(map2_, fileSize2_) == -1) {
	perror("Error un-mmapping file 2");
    }
    close(fd1_);
    close(fd2_);

  }

}

/*
 * Using this macro, only one component may live
 * in one library *and* you may *not* link this library
 * with another component library. Use
 * ORO_CREATE_COMPONENT_TYPE()
 * ORO_LIST_COMPONENT_TYPE(acc_cg)
 * In case you want to link with another library that
 * already contains components.
 *
 * If you have put your component class
 * in a namespace, don't forget to add it here too:
 */
ORO_CREATE_COMPONENT(acc::acc_cg)

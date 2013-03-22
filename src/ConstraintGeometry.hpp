#ifndef ACC_CONSTRAINT_GEOMETRY_HPP
#define ACC_CONSTRAINT_GEOMETRY_HPP

namespace acc {

class ConstraintGeometry {
  public:
    ConstraintGeometry() {};
    std::vector<float> vertices; //Maybe should change to ACTIVECORBA types...
    std::vector<long> triangles;
};

}
#endif

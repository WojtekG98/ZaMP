#ifndef CUBOID_HH
#define CUBOID_HH

#include "MobileObj.hh"
/*!
 * \brief Deklaracja instacji szablonu geom::Vector<int,3>
 */
 typedef geom::Vector<int,3>  VectorRGB;
/*!
 * \brief Zawiera definicje klasy Cuboid
 */
class Cuboid: public MobileObj {
  public:
	VectorRGB color;
};

#endif

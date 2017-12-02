#include "morpher/morpher.h"

void morpher_init(Morphing *morphing, IntVector width, IntVector height) {
  morphing->dim = (CartesianVector) {width, height};
}

void morpher_free(Morphing *morphing) {

}

void morpher_add_constraint(Morphing *morphing, CartesianVector origin, CartesianVector destination) {

}

CartesianMapping morpher_get_point_mapping(Morphing *morphing, CartesianVector point, TimeVector frame) {
  // TODO
  return (CartesianMapping) {point,
                             point};
}

CartesianVector morpher_get_dim(Morphing *morphing) {
  return morphing->dim;
}

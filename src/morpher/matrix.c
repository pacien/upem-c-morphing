#include "morpher/matrix.h"

IntVector matrix_int_det2(IntVector u11, IntVector u12,
                          IntVector u21, IntVector u22) {

  return u11 * u22 - u12 * u21;
}

IntVector matrix_int_det3(IntVector u11, IntVector u12, IntVector u13,
                          IntVector u21, IntVector u22, IntVector u23,
                          IntVector u31, IntVector u32, IntVector u33) {

  return u11 * matrix_int_det2(u22, u23, u32, u33)
         - u21 * matrix_int_det2(u12, u13, u32, u33)
         + u31 * matrix_int_det2(u12, u13, u22, u23);
}

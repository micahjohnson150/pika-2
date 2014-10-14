/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef GLSCOEFFICIENTKERNELTINTERFACE_H
#define GLSCOEFFICIENTKERNELTINTERFACE_H

// libMesh includes
#include "libmesh/libmesh_common.h"

// Forward declarations
class GLSCoefficientKernelInterface;
class InputParameters;
template <class T> class MaterialProperty;

template<>
InputParameters validParams<GLSCoefficientKernelInterface>();

/**
 * A class providing common functionality for GLS Kernels.
 */
class GLSCoefficientKernelInterface
{
public:
  GLSCoefficientKernelInterface(const std::string & name, InputParameters & parameters);

protected:

  /**
   * Returns the proper, scaled coefficient
   * @param The current quadrature point index, i.e., _qp
   * @return A scalar (libMesh::Real) containing the properly scaled coefficient
   */
  libMesh::Real coefficient(unsigned int qp);

  /// Flag indicating to use material property rather than scalar coefficient

  /// Scalar coefficient
  const libMesh::Real _coefficient;

};
#endif // GLSCOEFFICIENTKERNELINTERFACE_H
